/*
   Copyright © 2017-2019, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net

   Last modified: 2019-9-20

   Description: https://github.com/wlgq2/uv-cpp
*/
#include "RpcClient.h"

using namespace uv;
using namespace std;

RpcClient::RpcClient(EventLoop* loop, uv::SocketAddr& addr)
	:TcpClient(loop),
    addr_(addr),
    onResp_(nullptr)
{
    setConnectStatusCallback(std::bind(&RpcClient::onConnect,this,placeholders::_1));
    setMessageCallback(std::bind(&RpcClient::onMessage,this,placeholders::_1,placeholders::_2));
    connect(addr_);
}

RpcClient::~RpcClient()
{

}


void RpcClient::setOnResp(OnRespCallback callback)
{
    onResp_ = callback;
}

void RpcClient::onConnect(ConnectStatus status)
{
    if(status == ConnectStatus::OnConnectSuccess)
    {

    }
    else
    {
        uv::Timer* timer = new Timer(loop_, 50, 0,
            [this](Timer* timer)
        {
            connect(addr_);
            timer->close([this](Timer* timer)
            {
                delete timer;
            });
        });
        timer->start();
    }
}

void RpcClient::onMessage(const char* data,ssize_t size)
{
    if (nullptr == onResp_)
    {
        return;
    }
    Resp resp;
    if (0 == resp.unpack(data, (int)size))
    {
        onResp_(resp);
    }
}
