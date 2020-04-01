/*
   Copyright © 2017-2020, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net

   Last modified: 2020-3-30

   Description: https://github.com/wlgq2/uv-cpp
*/

#include "../include/http/Response.h"

using namespace uv;
using namespace uv::http;

Response::Response()
    :Response(HttpVersion::Http1_1, StatusCode::OK)
{
}

Response::Response(HttpVersion version, StatusCode code)
    :version_(version),
    statusCode_(code)
{
}

void Response::setVersion(HttpVersion version)
{
    version_ = version;
}

void Response::setStatusCode(StatusCode code)
{
    statusCode_ = code;
}

HttpVersion Response::getVersion()
{
    return version_;
}

Response::StatusCode Response::getStatusCode()
{
    return statusCode_;
}

void Response::appendHead(std::string& key, std::string& value)
{
    heads_[key] = value;
}

void Response::appendHead(std::string&& key, std::string&& value)
{
    heads_[key] = value;
}

std::string Response::getHead(std::string& key)
{
    auto it = heads_.find(key);
    if (it == heads_.end())
    {
        return "";
    }
    return it->second;
}

void Response::swapBody(std::string& body)
{
    body_.swap(body);
}

void Response::swapBody(std::string&& body)
{
    body.swap(body);
}

std::string& Response::getBody()
{
    return body_;
}

int Response::pack(std::string& data)
{
    return 0;
}

int Response::unpack(std::string& data)
{
    
    return 0;
}

int Response::unpackAndCompleted(std::string& data)
{
    int rst = unpack(data);
    if (rst == 0)
    {
        
    }
    return -1;
}