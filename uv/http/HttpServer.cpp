/*
   Copyright © 2017-2020, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net

   Last modified: 2020-4-6

   Description: https://github.com/wlgq2/uv-cpp
*/

#include "../include/http/HttpServer.h"

using namespace uv;
using namespace uv::http;

uv::http::HttpServer::HttpServer(EventLoop* loop)
    :uv::TcpServer(loop)
{
    setMessageCallback(std::bind(&HttpServer::onMesage,this,
        std::placeholders::_1,std::placeholders::_2,std::placeholders::_3));
}

void uv::http::HttpServer::Get(std::string path, OnHttpReqCallback callback)
{
    route_[Methon::Get].set(path, callback);
}

void uv::http::HttpServer::Post(std::string path, OnHttpReqCallback callback)
{
    route_[Methon::Post].set(path, callback);
}

void uv::http::HttpServer::Head(std::string path, OnHttpReqCallback callback)
{
    route_[Methon::Head].set(path, callback);
}

void uv::http::HttpServer::Put(std::string path, OnHttpReqCallback callback)
{
    route_[Methon::Put].set(path, callback);
}

void uv::http::HttpServer::Delete(std::string path, OnHttpReqCallback callback)
{
    route_[Methon::Delete].set(path, callback);
}

void uv::http::HttpServer::Connect(std::string path, OnHttpReqCallback callback)
{
    route_[Methon::Connect].set(path, callback);
}

void uv::http::HttpServer::Options(std::string path, OnHttpReqCallback callback)
{
    route_[Methon::Options].set(path, callback);
}

void uv::http::HttpServer::Trace(std::string path, OnHttpReqCallback callback)
{
    route_[Methon::Trace].set(path, callback);
}

void uv::http::HttpServer::Patch(std::string path, OnHttpReqCallback callback)
{
    route_[Methon::Patch].set(path, callback);
}

void uv::http::HttpServer::onMesage(TcpConnectionPtr conn, const char* data, ssize_t size)
{
    auto packetbuf = conn->getPacketBuffer();
    if (nullptr == packetbuf)
    {
        uv::LogWriter::Instance()->error("http server need use data buffer.");
        return;
    }
    packetbuf->append(data, size);
    std::string out;
    packetbuf->readBufferN(out, packetbuf->readSize());
    Request req;
    if (0 == req.unpack(out))

        packetbuf->clear();
        //int index = 
        //搜寻回调函数
    }
}