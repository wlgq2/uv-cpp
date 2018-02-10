#ifndef CLIENT_H
#define CLIENT_H


#include <string>
#include "uv/uv11.h"


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
    }

    void newMessage(const char* buf,unsigned int size)
    {
        write(buf,size,nullptr);
    }

private:
    std::shared_ptr<uv::SocketAddr> sockAddr;
};
#endif
