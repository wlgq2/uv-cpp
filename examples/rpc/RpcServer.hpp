/*
   Copyright © 2017-2020, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net

   Last modified: 2019-10-20

   Description: https://github.com/wlgq2/uv-cpp
*/

#ifndef RPC_SERVER_HPP
#define RPC_SERVER_HPP


#include <uv/include/uv11.hpp>
#include "protocol.hpp"

class RpcServer  : public uv::TcpServer
{
public:
	RpcServer(uv::EventLoop* loop);
	~RpcServer();

    template<typename Protocol>
    void sendProtocol(uv::TcpConnectionPtr connection,Protocol& req);
private:
    void onMessage(uv::TcpConnectionPtr connection,const char* buf,ssize_t size);

    void sum(Req& req, Resp& resp);
};

#endif

template<typename Protocol>
inline void RpcServer::sendProtocol(uv::TcpConnectionPtr connection, Protocol & req)
{
    int size = req.size();
    char* data = new char[size];
    req.pack(data, size);
    connection->writeInLoop(data, size,
        [this](uv::WriteInfo& info)
    {
        delete[] info.buf;
    });
}
