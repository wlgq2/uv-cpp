/*
Copyright © 2017-2020, orcaer@yeah.net  All rights reserved.

Author: orcaer@yeah.net

Last modified: 2018-4-18

Description: https://github.com/wlgq2/uv-cpp
*/

#ifndef ECHOSERVER_HPP
#define ECHOSERVER_HPP

#include "uv/include/uv11.hpp"


class EchoServer :public uv::TcpServer
{
public:
    EchoServer(uv::EventLoop* loop);
private :
    void newMessage(uv::TcpConnectionPtr connection,const char* buf,ssize_t size);
};

#endif
