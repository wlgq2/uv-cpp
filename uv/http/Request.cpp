/*
   Copyright © 2017-2020, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net

   Last modified: 2020-3-30

   Description: https://github.com/wlgq2/uv-cpp
*/

#include "../include/http/Request.h"

using namespace uv;
using namespace uv::http;

Request::Request()
    :Request(HttpVersion::Http1_1,Request::Methon::Get)
{
}

Request::Request(HttpVersion version, Methon methon)
    :version_(version),
    methon_(methon)
{
}

std::string& Request::getBody()
{
    return body_;
}

void Request::appendParam(std::string& key, std::string& value)
{
    params_[key] = value;
}

void Request::appendParam(std::string&& key, std::string&& value)
{
    params_[key] = value;
}

std::string Request::getParam(std::string& key)
{
    auto it = params_.find(key);
    if (it == params_.end())
    {
        return "";
    }
    return it->second;
}

void Request::setVersion(HttpVersion version)
{
    version_ = version;
}

void Request::setMethon(Methon methon)
{
    methon_ = methon;
}

void Request::setPath(std::string& path)
{
    path_ = path;
}

std::string& Request::getPath()
{
    return path_;
}

HttpVersion Request::getVersion()
{
    return version_;
}

Request::Methon Request::getMethon()
{
    return methon_;
}

int Request::pack(std::string& data)
{
    data.resize(1024);
    data.clear();
    data += MethonToStr(methon_);
    data += " ";
    if (path_.empty() || path_[0] == '/')
    {
        data += "/";
    }
    data += path_;
    data += " ";
    data += HttpVersionToStr(version_);
    data += Crlf;
    for (auto it = params_.begin();it != params_.end();it++)
    {
        data += it->first;
        data += ": ";
        data += it->second;
        data += Crlf;
    }
    data += Crlf;
    data += body_;
    return 0;
}

int Request::unpack(std::string& data)
{
    return 0;
}

std::string Request::MethonToStr(Methon methon)
{
    switch (methon)
    {
    case Get :
        return "GET";
    case Post :
        return "POST";
    case Head :
        return "HEAD";
    case Put:
        return "PUT";
    case Delete:
        return "DELETE";
    case Connect:
        return "CONNECT";
    case Options:
        return "OPTIONS";
    case Trace:
        return "TRACE";
    case Patch:
        return "PATCH";
    default:
        return "";
    }
}
