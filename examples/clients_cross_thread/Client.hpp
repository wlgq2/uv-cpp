/*
    Copyright © 2017-2019, orcaer@yeah.net  All rights reserved.

    Author: orcaer@yeah.net

    Last modified: 2018-4-18

    Description: https://github.com/wlgq2/uv-cpp
*/

#ifndef CLIENT_HPP
#define CLIENT_HPP


#include <string>
#include "uv/include/uv11.hpp"


class Client : public uv::TcpClient
{
public:
    Client(uv::EventLoop* loop);

    void connectToServer(uv::SocketAddr& addr);
    void reConnect();
    void onConnect(ConnectStatus status);
    void newMessage(const char* buf,ssize_t size);

private:
    std::shared_ptr<uv::SocketAddr> sockAddr;
};
#endif
