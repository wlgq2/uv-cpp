#include    <cstring>
#include    <iostream>

#include    "EchoServer.h"


using namespace uv;
using namespace std;

EchoServer::EchoServer(EventLoop* loop)
    :TcpServer(loop)
{
    cnt = 0;
    setMessageCallback(std::bind(&EchoServer::newMessage,this,placeholders::_1,placeholders::_2,placeholders::_3));
}

void EchoServer::newMessage(shared_ptr<TcpConnection> connection, const char* buf, ssize_t size)
{
    cnt++;
    //不使用buffer
    if (uv::GlobalConfig::BufferModeStatus == uv::GlobalConfig::NoBuffer)
    {
        connection->write(buf, size, nullptr);
    }
    else  //使用buffer
    {
        auto packetbuf = connection->getPacketBuffer();
        if (nullptr != packetbuf)
        {
            packetbuf->append(buf, static_cast<int>(size));
            //循环读取buffer
            Packet packet;
            while (0 == packetbuf->readPacket(packet))
            {   
                connection->write(packet.Buffer().c_str(), packet.PacketSize(), nullptr);
            }
        }
    }

}

uint64_t EchoServer::Cnt()
{
    return cnt;
}

void EchoServer::clearCnt()
{
    cnt =0;
}
