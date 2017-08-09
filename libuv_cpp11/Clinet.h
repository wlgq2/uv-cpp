#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include "uv/TcpClient.h"


class Client : public uv::TcpClient
{
public:
    Client(uv_loop_t* loop)
        :TcpClient(loop)
    {
        setConnectCloseCallback(std::bind(&Client::onConnectClose,this));
        setConnectCallback(std::bind(&Client::onConnect,this,std::placeholders::_1));
    }

    void onConnectClose()
    {
        connect("127.0.0.1",10010);
    }
    void onConnect(bool successed)
    {
        if(successed)
        {
            connect("127.0.0.1",10010);
        }
    }

    void newMessage(const char* buf,ssize_t size)
    {
        //write(buf,size,nullptr);
    }

};
#endif
