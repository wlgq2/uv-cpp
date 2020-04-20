#include <iostream>
#include <memory>
#include <atomic>
#include <vector>

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

void startRead(SocketPtr ptr);

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

void startClients(io_service& io,std::vector<SocketPtr>& sockets,ip::tcp::endpoint& endpoint, uint64_t cnt)
{
    for(uint64_t i=0;i<cnt;i++)
    {
        SocketPtr ptr = std::make_shared<SocketStr>();
        sockets.push_back(ptr);
        ptr->pSocket = std::make_shared<ip::tcp::socket>(io);
        ptr->pSocket->async_connect(endpoint, [ptr](const boost::system::error_code& error)
        {
            if(error)
            {
                std::cout<<"connect fail"<<std::endl;
                return;
            }
            uint64_t size = 1024*8;
            write(ptr,size);
        });
    }
}

int main(int argc, char* argv[])
{
    io_service io;
    std::vector<SocketPtr> sockets;
    ip::tcp::endpoint endpoint( ip::address::from_string("127.0.0.1"), 10012);
    startClients(io,sockets,endpoint,1);
    io.run();
}
