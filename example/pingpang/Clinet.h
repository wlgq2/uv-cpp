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
        setConnectCloseCallback(std::bind(&Client::onConnectClose,this));
        setConnectCallback(std::bind(&Client::onConnect,this,std::placeholders::_1));
        setMessageCallback(std::bind(&Client::newMessage,this,std::placeholders::_1,std::placeholders::_2));
    }

    void connectToServer(uv::SocketAddr& addr)
    {
        sockAddr = std::make_shared<uv::SocketAddr>(addr);
        connect(addr);
    }

    void onConnectClose()
    {
        connect(*(sockAddr.get()));
    }
    void onConnect(bool successed)
    {
        if(!successed)
        {
            connect(*(sockAddr.get()));
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

    void newMessage(const char* buf,unsigned int size)
    {
#if     USED_NO_PACKET
        write(data,1024);
#else
        uv::Packet packet;
        appendToBuffer(buf, size);
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
