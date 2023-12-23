#include <iostream>
#include <memory>
#include <atomic>

#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace boost::asio;

struct SocketStr
{
    std::shared_ptr<ip::tcp::socket> pSocket;
    char readBuffer[1024*32];
    char writeBuffer[1024*32];
};
using SocketPtr = std::shared_ptr<SocketStr>;

void startAccept(io_service& io,ip::tcp::acceptor& acceptor);
void startRead(SocketPtr ptr);
void startTimer(deadline_timer& timer);

std::atomic<uint64_t> cnt(0);

void write(SocketPtr ptr,size_t size)
{
    ptr->pSocket->async_write_some( buffer(ptr->writeBuffer, size), [ptr](const boost::system::error_code& error,std::size_t size)
    {
        startRead(ptr);
    });
}

void onRead(SocketPtr ptr,const boost::system::error_code& error,std::size_t size)
{
    if(error)
    {
        return;
    }
    cnt += size;
    std::copy(ptr->readBuffer, ptr->readBuffer+size, ptr->writeBuffer);
    write(ptr,size);
}

void startRead(SocketPtr ptr)
{
    auto pSocket = ptr->pSocket;
    auto buff = ptr->readBuffer;
    uint64_t size = sizeof(ptr->readBuffer);
    pSocket->async_read_some(buffer(buff,size),std::bind(&onRead,ptr,std::placeholders::_1,std::placeholders::_2));
}

void onNewConnection(io_service& io,ip::tcp::acceptor& acceptor, SocketPtr ptr,boost::system::error_code error)
{
    if(error)
    {
        return;
    }
    startRead(ptr);
    startAccept(io,acceptor);
}

void startAccept(io_service& io,ip::tcp::acceptor& acceptor)
{
    SocketPtr ptr = std::make_shared<SocketStr>();
    ptr->pSocket = std::make_shared<ip::tcp::socket>(io);
    acceptor.async_accept(*(ptr->pSocket), std::bind(&onNewConnection,std::ref(io),std::ref(acceptor),ptr,std::placeholders::_1));
}

void onTimer(deadline_timer& timer,const boost::system::error_code &ec)
{
    std::cout << "send data:" << (cnt >> 10) << " kbyte/s" << std::endl;
    cnt = 0;
    startTimer(timer);
}

void startTimer(deadline_timer& timer)
{
    timer.expires_at(timer.expires_at()+ boost::posix_time::milliseconds(1000));
    timer.async_wait(std::bind(&onTimer,std::ref(timer),std::placeholders::_1));
}

int main(int argc, char* argv[])
{
    io_service io;
    ip::tcp::acceptor acceptor(io, ip::tcp::endpoint(ip::tcp::v4(), 10012));
    startAccept(io,acceptor);

    deadline_timer timer(io, boost::posix_time::milliseconds(1000));
    startTimer(timer);

    io.run();
}
