/*
   Copyright © 2017-2019, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net

   Last modified: 2019-9-20

   Description: https://github.com/wlgq2/uv-cpp
*/


#ifndef RPC_CLIENT_H
#define RPC_CLIENT_H

#include <uv/include/uv11.h>
#include "protocol.h"

using OnRespCallback = std::function<void(Resp&)>;

class RpcClient : public uv::TcpClient
{
public:
	RpcClient(uv::EventLoop* loop,uv::SocketAddr& addr);
	virtual ~RpcClient();

    template<typename Protocol>
    void sendProtocol(Protocol& req);

    void setOnResp(OnRespCallback callback);
private:
    void onConnect(ConnectStatus status);
    void onMessage(const char* data,ssize_t size);

private:
    uv::SocketAddr addr_;
    OnRespCallback onResp_;
};


template<typename Protocol>
inline void RpcClient::sendProtocol(Protocol& req)
{
    int size = req.size();
    char* data = new char[size];
    req.pack(data, size);
    std::string str;
    uv::LogWriter::ToHex(str, data, size);
    writeInLoop(data, size,
        [this](uv::WriteInfo& info)
    {
        delete[] info.buf;
    });
}

#endif


