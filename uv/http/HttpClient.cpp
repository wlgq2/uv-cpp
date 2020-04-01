/*
   Copyright © 2017-2020, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net

   Last modified: 2020-3-30

   Description: https://github.com/wlgq2/uv-cpp
*/

#include "../include/http/HttpClient.h"

using namespace uv;
using namespace uv::http;

HttpClient::HttpClient(EventLoop* loop)
    :client_(new TcpClient(loop)),
    callback_(nullptr)
{
    buffer_.resize(20480);
}

HttpClient::~HttpClient()
{
    auto client = client_;
    client->close([client](std::string& name)
    {
        delete client;
    });
}


void HttpClient::Req(uv::SocketAddr& addr,Request& req)
{
    req_ = req;
    buffer_.clear();
    client_->setConnectStatusCallback(std::bind(&HttpClient::onConnectStatus,this,std::placeholders::_1));
    client_->setMessageCallback(std::bind(&HttpClient::onMessage, this, std::placeholders::_1, std::placeholders::_2));
    client_->connect(addr);
}

void HttpClient::setOnResp(OnRespCallback callback)
{
    callback_ = callback;
}

void HttpClient::onResp(int rst, Response* resp)
{
    if (nullptr != callback_)
    {
        callback_(rst, resp);
    }
}

void HttpClient::onConnectStatus(TcpClient::ConnectStatus status)
{
    if (status == uv::TcpClient::ConnectStatus::OnConnectSuccess)
    {
        std::string str;
        req_.pack(str);
        client_->write(str.c_str(), (unsigned int)str.size());
    }
    else if (status == uv::TcpClient::ConnectStatus::OnConnnectFail)
    {
        onResp(ConnectFail, nullptr);
    }
    else
    {
        Response resp;
        if (0 == resp.unpack(buffer_))
        {
            onResp(Success, &resp);
        }
        else
        {
            onResp(ParseFail, nullptr);
        }
    }
}

void HttpClient::onMessage(const char* data, ssize_t size)
{
    unsigned bufsize = (unsigned)buffer_.size();
    unsigned datasize = bufsize + (unsigned)size;
    buffer_.resize(datasize);
    char* out = (char*)buffer_.c_str() + bufsize;
    std::copy(data, data + size, out);

    Response resp;
    if (0 == resp.unpackAndCompleted(buffer_))
    {
        onResp(Success, &resp);
    }
}
