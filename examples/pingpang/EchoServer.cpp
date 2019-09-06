#include    <cstring>
#include    <iostream>

#include    "EchoServer.h"


using namespace uv;
using namespace std;

EchoServer::EchoServer(EventLoop* loop, SocketAddr& addr)
    :TcpServer(loop, addr)
{
    cnt = 0;
    setMessageCallback(std::bind(&EchoServer::newMessage,this,placeholders::_1,placeholders::_2,placeholders::_3));
}

void EchoServer::newMessage(shared_ptr<TcpConnection> connection,const char* buf,ssize_t size)
{

#if     USED_NO_PACKET
    cnt++;
    connection->write(buf,size,nullptr);
#else
    uv::Packet packet;
    connection->appendToBuffer(buf, size);
    while (0 == connection->readFromBuffer(packet))
    {
        cnt++;
        connection->write(packet.Buffer(), packet.BufferSize(), nullptr);
    }
#endif

}

uint64_t EchoServer::Cnt()
{
    return cnt;
}

void EchoServer::clearCnt()
{
    cnt =0;
}
