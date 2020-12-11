/*
   Copyright © 2017-2020, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net

   Last modified: 2020-3-30

   Description: https://github.com/wlgq2/uv-cpp
*/

#include "../include/http/Request.hpp"

using namespace uv;
using namespace uv::http;

Request::Request()
    :Request(HttpVersion::Http1_1,Methon::Get)
{
}

Request::Request(HttpVersion version, Methon methon)
    :version_(version),
    methon_(methon)
{
}

void Request::swapContent(std::string& str)
{
    content_.swap(str);
}

void Request::swapContent(std::string&& str)
{
    swapContent(str);
}

const std::string& Request::getContent()
{
    return content_;
}

void Request::appendHead(std::string& key, std::string& value)
{
    heads_[key] = value;
}

void Request::appendHead(std::string&& key, std::string&& value)
{
    heads_[key] = value;
}

std::string Request::getHead(std::string& key)
{
    auto it = heads_.find(key);
    if (it == heads_.end())
    {
        return "";
    }
    return it->second;
}

std::string Request::getHead(std::string&& key)
{
    return getHead(key);
}

void Request::appendUrlParam(std::string& key, std::string& value)
{
    urlParms_[key] = value;
}

void Request::appendUrlParam(std::string&& key, std::string&& value)
{
    urlParms_[key] = value;
}

std::string Request::getUrlParam(std::string& key)
{
    auto it = urlParms_.find(key);
    if (it != urlParms_.end())
    {
        return it->second;
    }
    return "";
}

std::string Request::getUrlParam(std::string&& key)
{
    return getUrlParam(key);
}

void Request::setVersion(HttpVersion version)
{
    version_ = version;
}

void Request::setMethon(Methon methon)
{
    methon_ = methon;
}

void Request::setPath(std::string&& path)
{
    setPath(path);
}

void Request::setPath(std::string& path)
{
    path_ = path;
}

const std::string& Request::getValue()
{
    return value_;
}

const std::string& Request::getPath()
{
    return path_;
}

HttpVersion Request::getVersion()
{
    return version_;
}

Methon Request::getMethon()
{
    return methon_;
}

int Request::pack(std::string& data)
{
    data.resize(1024);
    data.clear();
    data += MethonToStr(methon_);
    data += " ";
    packPathParam(data);
    data += " ";
    data += HttpVersionToStr(version_);
    data.append(Crlf, sizeof(Crlf));
    for (auto it = heads_.begin();it != heads_.end();it++)
    {
        data += it->first;
        data += ": ";
        data += it->second;
        data.append(Crlf, sizeof(Crlf));
    }
    data.append(Crlf, sizeof(Crlf));
    data += content_;
    return 0;
}


ParseResult Request::unpack(std::string& data)
{
    std::vector<std::string> headList;
    auto pos = SplitHttpOfCRLF(data, headList);
    if (pos == -1)
    {
        //解析失败
        return ParseResult::Fail;
    }
    //解析状态行
    if (unpackUrl(headList[0]) != 0)
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
    //conent数据
    content_ = std::string(data, pos + 4);
    return ParseResult::Success;
}

ParseResult Request::unpackAndCompleted(std::string & data)
{
    auto rst = unpack(data);
    if (rst == ParseResult::Success)
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
                if (size == content_.size())
                {
                    return ParseResult::Success;
                }
                return ParseResult::Fail;
            }
            catch (...)
            {
                return ParseResult::Success;
            }
        }
    }
    return rst;
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

Methon uv::http::Request::StrToMethon(std::string& str)
{
    if (str == "GET")
    {
        return Methon::Get;
    }
    if (str == "POST")
    {
        return Methon::Post;
    }
    if (str == "HEAD")
    {
        return Methon::Head;
    }
    if (str == "PUT")
    {
        return Methon::Put;
    }
    if (str == "DELETE")
    {
        return Methon::Delete;
    }
    if (str == "CONNECT")
    {
        return Methon::Connect;
    }
    if (str == "OPTIONS")
    {
        return Methon::Options;
    }
    if (str == "TRACE")
    {
        return Methon::Trace;
    }
    if (str == "PATCH")
    {
        return Methon::Patch;
    }
    return Methon::Invalid;
}

void uv::http::Request::packPathParam(std::string& path)
{
    if (path_.empty() || path_[0] != '/')
    {
        path += "/";
    }
    path += path_;
    if (urlParms_.size() > 0)
    {
        path += "?";
        for (auto& ele : urlParms_)
        {
            path += ele.first;
            path += "=";
            path += ele.second;
            path += "&";
        }
        path.pop_back();
    }

}

int uv::http::Request::unpackUrl(std::string& str)
{
    std::vector<std::string> out;
    SplitStrOfSpace(str, out);
    if (out.size() != 3)
    {
        //解析失败
        return -1;
    }
    methon_ = StrToMethon(out[0]);
    if (methon_ == Methon::Invalid)
    {
        return -1;
    }
    if (0 != unpackPath(out[1]))
    {
        return -1;
    }
    version_ = GetHttpVersion(out[2]);

    return 0;
}

int uv::http::Request::unpackPath(std::string& str)
{
    urlParms_.clear();
    auto pos = str.find(":");
    if (pos != str.npos)
    {
        std::string temp(str, 0, pos + 1);
        path_.swap(temp);
        std::string value(str, pos + 1, str.size() - pos - 1);
        value_.swap(value);
        return 0;
    }
    pos = str.find("?");
    std::string temp(str, 0, pos);
    path_.swap(temp);
    for (auto i = pos ;i < str.size();)
    {
        auto p = str.find("=", i);
        if (p == str.npos)
        {
            break;
        }
        if (p - i < 1)
        {
            break;
        }
        std::string key(str, i + 1, p - i - 1);
        i = p;
        p = str.find("&", i);
        if (p == str.npos)
        {
            p = str.size();
        }
        if (p - i < 1)
        {
            break;
        }
        std::string value(str, i + 1, p - i - 1);
        urlParms_[key] = value;
        i = p;
    }
    return 0;
}
