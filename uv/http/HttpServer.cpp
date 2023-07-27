/*
   Copyright © 2017-2020, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net

   Last modified: 2020-4-6

   Description: https://github.com/wlgq2/uv-cpp
*/

#include "../include/http/HttpServer.hpp"

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
    route_[Method::Get].set(path, callback);
}

void uv::http::HttpServer::Post(std::string path, OnHttpReqCallback callback)
{
    route_[Method::Post].set(path, callback);
}

void uv::http::HttpServer::Head(std::string path, OnHttpReqCallback callback)
{
    route_[Method::Head].set(path, callback);
}

void uv::http::HttpServer::Put(std::string path, OnHttpReqCallback callback)
{
    route_[Method::Put].set(path, callback);
}

void uv::http::HttpServer::Delete(std::string path, OnHttpReqCallback callback)
{
    route_[Method::Delete].set(path, callback);
}

void uv::http::HttpServer::Connect(std::string path, OnHttpReqCallback callback)
{
    route_[Method::Connect].set(path, callback);
}

void uv::http::HttpServer::Options(std::string path, OnHttpReqCallback callback)
{
    route_[Method::Options].set(path, callback);
}

void uv::http::HttpServer::Trace(std::string path, OnHttpReqCallback callback)
{
    route_[Method::Trace].set(path, callback);
}

void uv::http::HttpServer::Patch(std::string path, OnHttpReqCallback callback)
{
    route_[Method::Patch].set(path, callback);
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
    auto rst = req.unpackAndCompleted(out);
    if (ParseResult::Error == rst)
    {
        //parse error,clear buffer.
        packetbuf->clear();
    }
    else if (ParseResult::Success == rst)
    {
        packetbuf->clear();
        //搜寻回调函数
        OnHttpReqCallback callback(nullptr);
        if (route_[req.getMethod()].get(req.getPath(), callback))
        {
            if (nullptr != callback)
            {
                Response resp;
                callback(req, &resp);
                std::string respData;
                resp.pack(respData);
                std::string connName = conn->Name();
                conn->write(respData.c_str(), respData.size(), [this, connName](WriteInfo&)
                {
                    closeConnection(connName);
                });

            }
        }
    }
    else ; //parse fail.
}