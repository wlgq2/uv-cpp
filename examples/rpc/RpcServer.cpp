/*
   Copyright © 2017-2019, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net

   Last modified: 2019-10-20

   Description: https://github.com/wlgq2/uv-cpp
*/

#include "RpcServer.h"

using namespace uv;
using namespace std;

RpcServer::RpcServer(EventLoop* loop)
	:TcpServer(loop)
{
    setMessageCallback(std::bind(&RpcServer::onMessage,this,placeholders::_1,placeholders::_2,placeholders::_3));
}

RpcServer::~RpcServer()
{

}

void RpcServer::onMessage(uv::TcpConnectionPtr connection,const char* buf,ssize_t size)
{
    Req req;
    if (0 == req.unpack(buf, (int)size))
    {
        Resp resp;
        sum(req, resp);
        sendProtocol(connection, resp);
    }
}

void RpcServer::sum(Req& req, Resp& resp)
{
    resp.param = 0;
    for (auto param : req.params)
    {
        resp.param += param;
    }
}
