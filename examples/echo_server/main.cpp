/*
    Copyright © 2017-2019, orcaer@yeah.net  All rights reserved.

    Author: orcaer@yeah.net

    Last modified: 2019-10-20

    Description: https://github.com/wlgq2/uv-cpp
*/

#include <iostream>

#include "EchoServer.h"

using namespace uv;


int main(int argc, char** args)
{
    EventLoop* loop = EventLoop::DefaultLoop();

    SocketAddr addr("0.0.0.0", 10005, SocketAddr::Ipv4);

    EchoServer server(loop);
    //心跳超时
    server.setTimeout(40);
    server.bindAndListen(addr);
    loop->run();
}
