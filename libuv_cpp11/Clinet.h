#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>
#include "uv/TcpClient.h"


class Client : public uv::TcpClient
{
public:
    Client(uv_loop_t* loop)
        :TcpClient(loop)
    {
        setConnectCloseCallback(std::bind(&Client::onConnectClose,this));
        setConnectCallback(std::bind(&Client::onConnect,this,std::placeholders::_1));
        setMessageCallback(std::bind(&Client::newMessage,this,std::placeholders::_1,std::placeholders::_2));
    }

    void connectToServer(std::string& ip,int port)
    {
        this->port = port;
        this->ip = ip;
        std::cout<<ip<<port<<std::endl;
        connect(ip.c_str(),port);
    }

    void onConnectClose()
    {
        connect(ip.c_str(),port);
    }
    void onConnect(bool successed)
    {
        if(!successed)
        {
            connect(ip.c_str(),port);
        }
    }

    void newMessage(const char* buf,unsigned int size)
    {
        write(buf,size,nullptr);
    }

private:
    std::string ip;
    int port;
};
#endif
