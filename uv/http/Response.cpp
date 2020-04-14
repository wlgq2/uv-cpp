/*
   Copyright © 2017-2020, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net

   Last modified: 2020-3-30

   Description: https://github.com/wlgq2/uv-cpp
*/

#include "../include/http/Response.h"
#include "../include/LogWriter.h"

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

void Response::setStatus(StatusCode code, std::string info)
{
    statusCode_ = code;
    statusInfo_ = info;
}

HttpVersion Response::getVersion()
{
    return version_;
}

Response::StatusCode Response::getStatusCode()
{
    return statusCode_;
}

std::string& Response::getStatusInfo()
{
    return statusInfo_;
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

void Response::swapContent(std::string& body)
{
    content_.swap(body);
}

void Response::swapContent(std::string&& body)
{
    content_.swap(body);
}

std::string& Response::getContent()
{
    return content_;
}

int Response::pack(std::string& data)
{
    data.resize(100 * heads_.size() + content_.size());
    data.clear();
    data += HttpVersionToStr(version_);
    data += " ";
    data += std::to_string(statusCode_);
    data += " ";
    data += content_;
    data += Crlf;
    for (auto it = heads_.begin();it != heads_.end();it++)
    {
        data += it->first;
        data += ": ";
        data += it->second;
        data += Crlf;
    }
    data += Crlf;
    data += content_;
    return 0;
}

int Response::unpack(std::string& data)
{
    std::vector<std::string> headList;
    auto pos = SplitHttpOfCRLF(data, headList);
    if (pos == -1)
    {
        //解析失败
        return ParseResult::Fail;
    }
    //解析状态行
    if (parseStatus(headList[0]) != 0)
    {
        return ParseResult::Error;
    }
    //解析消息头
    for (uint64_t i = 1; i < headList.size(); i++)
    {
        if (AppendHead(headList[i],heads_) != 0)
        {
            return ParseResult::Error;
        }
    }
    //body数据
    content_ = std::string(data, pos + 4);
    return ParseResult::Success;
}

int Response::unpackAndCompleted(std::string& data)
{
    int rst = unpack(data);
    if (rst == 0)
    {
        auto it = heads_.find("Content-Length");
        if (it == heads_.end())
        {
            it = heads_.find("content-length");
        }
        if (it != heads_.end())
        {
            try
            {
                uint64_t size = std::stoi(it->second);
                return size != content_.size();
            }
            catch (...)
            {

            }
        }
        else
        {
            it = heads_.find("Transfer-Encoding");
            if (it != heads_.end() && it->second == "chunked")
            {
                return isCompletedChunked();
            }
        }
    }
    return -1;
}

int Response::isCompletedChunked()
{
    auto pos = content_.find("0\r\n\r\n");
    if (pos == content_.npos)
    {
        return -1;
    }
    std::string temp;
    int p2 = -1;
    for (int p1 = 0;true;)
    {
        p1 = content_.find("\r\n", p2 + 1);
        if (p1 == content_.npos)
        {
            break;
        }

        p2 = content_.find("\r\n", p1 + 1);
        if (p2 == content_.npos)
        {
            break;
        }
        temp += content_.substr(p1 + 2, p2 - p1 - 2);
    }
    content_.swap(temp);
    return 0;
}

int Response::parseStatus(std::string& str)
{
    std::vector<std::string> out;
    SplitStrOfSpace(str, out);
    if (out.size() != 3)
    {
        //解析失败
        return -1;
    }
    version_ = GetHttpVersion(out[0]);

    try
    {
        statusCode_ = (StatusCode)std::stoi(out[1]);
        statusInfo_ = out[2];
    }
    catch (...)
    {
        return -1;
    }
    return 0;
}
