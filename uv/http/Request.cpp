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

int uv::http::Request::pack(std::string & data)
{
    return 0;
}

int uv::http::Request::unpack(std::string & data)
{
    return 0;
}
