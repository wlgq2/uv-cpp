/*
    Copyright 2017, orcaer@yeah.net  All rights reserved.

    Author: orcaer@yeah.net

    Last modified: 2018-4-18

    Description: https://github.com/wlgq2/libuv_cpp11
*/

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
        if(successed)
        {
            //send packet
            char data[] = "test message";
            uv::Packet packet;
            packet.reserve_ = 655;
            packet.fill(data, sizeof(data));
            write(packet.Buffer(),packet.BufferSize());
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
