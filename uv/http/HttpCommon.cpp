/*
   Copyright © 2017-2020, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net

   Last modified: 2020-3-31

   Description: https://github.com/wlgq2/uv-cpp
*/

#include "../include/http/HttpCommon.h"

using namespace uv;
using namespace uv::http;

std::string uv::http::HttpVersionToStr(HttpVersion version)
{
    switch (version)
    {
    case uv::http::Http1_0:
        return "HTTP/1.0";
    case uv::http::Http1_1:
        return "HTTP/1.1";
    default:
        return "";
    }
}

HttpVersion uv::http::GetHttpVersion(std::string & str)
{
    if (str == "HTTP/1.0")
    {
        return Http1_0;
    }
    if (str == "HTTP/1.1")
    {
        return Http1_1;
    }
    return Unknown;
}

int uv::http::SplitHttpOfCRLF(std::string& str, std::vector<std::string>& out, int defaultSize)
{
    auto bodyPos = str.find("\r\n\r\n");
    if (bodyPos == str.npos)
    {
        //解析失败，未找到消息正文
        return -1;
    }
    out.resize(defaultSize);
    out.clear();
    for (size_t pos = 0; pos < bodyPos;)
    {
        auto last = pos;
        pos = str.find("\r\n",pos+1);
        if (pos == str.npos)
        {
            break;
        }
        if (0 != last)
        {
            last += 2;
        }
        out.push_back(std::string(str, last, pos-last));
    }
    return (int)bodyPos;
}

int uv::http::SplitStrOfSpace(std::string& str, std::vector<std::string>& out, int defaultSize)
{
    for (size_t pos = 0; pos != str.size();)
    {
        auto last = pos;
        pos = str.find(" ", pos + 1);
        if (pos == last + 1)
        {
            continue;
        }
        if (last != 0)
        {
            last += 1;
        }
        if (pos == str.npos)
        {
            pos = str.size();
        }
        out.push_back(std::string(str, last, pos - last));
    }
    return 0;
}
