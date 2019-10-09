/*
   Copyright © 2017-2019, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net

   Last modified: 2019-9-20

   Description: https://github.com/wlgq2/uv-cpp
*/

#include "RpcCtrl.h"
#include <thread>
#include "RpcClient.h"


using namespace uv;
using namespace std;

RpcCtrl::RpcCtrl(uv::SocketAddr& addr)
    :addr_(addr)
{
    std::thread back(std::bind(&RpcCtrl::backRun, this));
    back.detach();
    this_thread::sleep_for(chrono::milliseconds(200));
}

RpcCtrl::~RpcCtrl()
{
}

void RpcCtrl::sum(Req& req, Resp& resp)
{
    std::unique_lock<std::mutex> lock(mutex_);
    ready_ = false;
    client_->sendProtocol(req);
    condition_.wait(lock, [this]()
    {
        return ready_;
    });
    resp = resp_;
}

void RpcCtrl::onResp(Resp& resp)
{
    std::unique_lock<std::mutex> lock(mutex_);
    resp_ = resp;
    ready_ = true;
    condition_.notify_one();
}

void RpcCtrl::backRun()
{
    uv::EventLoop loop;
    client_ = new RpcClient(&loop, addr_);
    client_->setOnResp(std::bind(&RpcCtrl::onResp, this, placeholders::_1));
    loop.run();
    //event's loop not run, so can delete.
    delete client_;
}
