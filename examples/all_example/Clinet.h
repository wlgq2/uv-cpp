/*
    Copyright © 2017-2019, orcaer@yeah.net  All rights reserved.

    Author: orcaer@yeah.net

    Last modified: 2018-4-18

    Description: https://github.com/wlgq2/uv-cpp
*/

#ifndef CLIENT_H
#define CLIENT_H


#include <string>
#include "uv/include/uv11.h"


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
            //重连
            reConnect();
        }
        else
        {
            char data[] = "test message";
            if (uv::GlobalConfig::BufferModeStatus == uv::GlobalConfig::NoBuffer)
            {
                write(data, (int)sizeof(data));
            }
            else
            {
                uv::Packet packet;
                packet.pack(data, sizeof(data));
                write(packet.Buffer().c_str(), packet.PacketSize());
            }
        }
    }

    void newMessage(const char* buf,ssize_t size)
    {
        //write(buf, (unsigned)size, nullptr);
    }

private:
    std::shared_ptr<uv::SocketAddr> sockAddr;
};
#endif
