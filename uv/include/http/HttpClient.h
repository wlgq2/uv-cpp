/*
   Copyright © 2017-2020, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net

   Last modified: 2020-3-30

   Description: https://github.com/wlgq2/uv-cpp
*/

#ifndef UV_HTTP_CLIENT_H
#define UV_HTTP_CLIENT_H

#include "../TcpClient.h"
#include "Request.h"
#include "Response.h"

namespace uv
{
namespace http
{

class HttpClient 
{
public:
    using OnRespCallback = std::function<void(int,Response*)>;
    enum ReqResult
    {
        Success = 0,
        ConnectFail = 1,
        ParseFail = 2,
        Unknow = 3,
    };

public:
    HttpClient(EventLoop* loop);
    virtual ~HttpClient();

    void Req(uv::SocketAddr& addr,Request& req);

    void setOnResp(OnRespCallback callback);

private:
    TcpClient* client_;
    OnRespCallback callback_;
    Request req_;
    std::string buffer_;

private:
    void onResp(int rst, Response* resp);
    void onConnectStatus(TcpClient::ConnectStatus status);
    void onMessage(const char* data, ssize_t size);
    bool isConnected;
};

}
}
#endif
