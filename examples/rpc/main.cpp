/*
   Copyright © 2017-2019, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net

   Last modified: 2019-9-20

   Description: https://github.com/wlgq2/uv-cpp
*/

#include <thread>
#include <iostream>
#include <chrono>

#include "RpcServer.h"
#include "RpcCtrl.h"

using namespace std;

void runRpcServer(uv::SocketAddr& addr)
{
    thread back([&addr]()
    {
        uv::EventLoop loop;
        RpcServer server(&loop);
        server.bindAndListen(addr);
        loop.run();
    });
    back.detach();
    this_thread::sleep_for(chrono::milliseconds(200));
}

int main(int argc, char** args)
{
    //rpc server
    uv::SocketAddr addr("127.0.0.1", 10000);
    runRpcServer(addr);

    //rpc contrl
    RpcCtrl rpc(addr);
    Req req;
    for (auto i = 1; i <= 100; i++)
    {
        req.params.push_back(i);
    }

    Resp resp;
    rpc.sum(req, resp);
    std::cout << "1~100 sum :"<<resp.param << std::endl;
}
