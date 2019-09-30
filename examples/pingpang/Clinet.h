#ifndef CLIENT_H
#define CLIENT_H


#include <string>
#include "uv/uv11.h"
#include "ModeDefine.h"

class Client : public uv::TcpClient
{
public:
    Client(uv::EventLoop* loop)
        :TcpClient(loop),
        sockAddr(nullptr)
    {
        setConnectStatusCallback(std::bind(&Client::onConnect,this,std::placeholders::_1));
        setMessageCallback(std::bind(&Client::newMessage,this,std::placeholders::_1,std::placeholders::_2));
    }

    void connectToServer(uv::SocketAddr& addr)
    {
        sockAddr = std::make_shared<uv::SocketAddr>(addr);
        connect(addr);
    }

    void reConnect()
    {
        uv::Timer* timer = new uv::Timer(Loop(), 1000, 0, [this](uv::Timer* timer)
        {
            connect(*(sockAddr.get()));
            timer->close([](uv::Timer* handle)
            {
                delete handle;
            });
        });
        timer->start();
    }

    void onConnect(TcpClient::ConnectStatus status)
    {
        if(status != TcpClient::ConnectStatus::OnConnectSuccess)
        {
            reConnect();
        }
        else
        {
#if     USED_NO_PACKET
            write(data,1024);
#else
            uv::Packet packet;
            packet.fill(data,1024);

            write(packet.Buffer(), packet.BufferSize(), nullptr);
#endif
        }
    }

    void newMessage(const char* buf,ssize_t size)
    {
#if     USED_NO_PACKET
        write(data, (unsigned int)size);
#else
        uv::Packet packet;
        appendToBuffer(buf, (int)size);
        while (0 == readFromBuffer(packet))
        {
            write(packet.Buffer(), packet.BufferSize(), nullptr);
        }
#endif
    }

private:
    std::shared_ptr<uv::SocketAddr> sockAddr;
    char data[10000];
};
#endif
