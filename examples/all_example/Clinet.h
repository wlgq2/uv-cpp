/*
    Copyright © 2017-2019, orcaer@yeah.net  All rights reserved.

    Author: orcaer@yeah.net

    Last modified: 2018-4-18

    Description: https://github.com/wlgq2/uv-cpp
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
        uv::Timer* timer = new uv::Timer(loop_, 500, 0, [this](uv::Timer* ptr)
        {
            connect(*(sockAddr.get()));
            ptr->close([](uv::Timer* ptr)
            {
                delete ptr;
            });
        });
        timer->start();

    }
    void onConnect(ConnectStatus status)
    {
        if(status != ConnectStatus::OnConnectSuccess)
        {
            //оп┴г
            reConnect();
        }
        else
        {
#if    1
            char data[1024] = "test message";
            write(data,(int)sizeof(data));
#else
            //send packet
            char data[] = "test message";
            uv::Packet packet;
            packet.reserve_ = 655;
            packet.fill(data, sizeof(data));
            write(packet.Buffer(),packet.BufferSize());
#endif
        }
    }

    void newMessage(const char* buf,ssize_t size)
    {
        write(buf, (unsigned)size, nullptr);
    }

private:
    std::shared_ptr<uv::SocketAddr> sockAddr;
};
#endif
