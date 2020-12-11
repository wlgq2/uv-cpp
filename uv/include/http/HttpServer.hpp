/*
   Copyright © 2017-2020, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net

   Last modified: 2020-4-5

   Description: https://github.com/wlgq2/uv-cpp
*/

#ifndef UV_HTTP_SERVER_HPP
#define UV_HTTP_SERVER_HPP

#include "../TcpServer.hpp"
#include "RadixTree.hpp"
#include "Request.hpp"
#include "Response.hpp"

namespace uv
{
namespace http
{

class HttpServer : public uv::TcpServer
{
public:
    using OnHttpReqCallback = std::function<void(Request&,Response*)>;

public:
    HttpServer(EventLoop* loop);
    void Get(std::string path, OnHttpReqCallback callback);
    void Post(std::string path, OnHttpReqCallback callback);
    void Head(std::string path, OnHttpReqCallback callback);
    void Put(std::string path, OnHttpReqCallback callback);
    void Delete(std::string path, OnHttpReqCallback callback);
    void Connect(std::string path, OnHttpReqCallback callback);
    void Options(std::string path, OnHttpReqCallback callback);
    void Trace(std::string path, OnHttpReqCallback callback);
    void Patch(std::string path, OnHttpReqCallback callback);

private:
    RadixTree<OnHttpReqCallback> route_[Methon::Invalid];

    void onMesage(TcpConnectionPtr conn, const char* data, ssize_t size);


};

}
}
#endif
