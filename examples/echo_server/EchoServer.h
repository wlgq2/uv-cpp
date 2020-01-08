/*
Copyright © 2017-2019, orcaer@yeah.net  All rights reserved.

Author: orcaer@yeah.net

Last modified: 2018-4-18

Description: https://github.com/wlgq2/uv-cpp
*/

#ifndef ECHOSERVER_H
#define ECHOSERVER_H

#include "uv/include/uv11.h"


class EchoServer :public uv::TcpServer
{
public:
    EchoServer(uv::EventLoop* loop);
private :
    void newMessage(uv::TcpConnectionPtr connection,const char* buf,ssize_t size);
};

#endif // ECHOSERVER_H
