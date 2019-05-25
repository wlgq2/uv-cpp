/*
Copyright 2017, orcaer@yeah.net  All rights reserved.

Author: orcaer@yeah.net

Last modified: 2018-4-18

Description: https://github.com/wlgq2/libuv_cpp11
*/

#ifndef ECHOSERVER_H
#define ECHOSERVER_H

#include "uv/uv11.h"


class EchoServer :public uv::TcpServer
{
public:
    EchoServer(uv::EventLoop* loop, uv::SocketAddr& addr);
private :
    void newMessage(std::shared_ptr<uv::TcpConnection> connection,const char* buf,ssize_t size);
};

#endif // ECHOSERVER_H
