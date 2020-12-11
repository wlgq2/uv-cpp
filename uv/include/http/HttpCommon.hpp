/*
   Copyright © 2017-2020, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net

   Last modified: 2020-3-30

   Description: https://github.com/wlgq2/uv-cpp
*/

#ifndef UV_HTTP_COMMON_HPP
#define UV_HTTP_COMMON_HPP

#include <string>
#include <vector>
#include <map>

namespace uv
{
namespace http
{
enum ParseResult
{
    Success = 0, //解析成功
    Fail,//解析失败
    Error,//解析出错
};

enum HttpVersion
{
    Unknown,
    Http1_0,
    Http1_1,
};

enum Methon
{
    Get = 0,
    Post,
    Head,
    Put,
    Delete,
    Connect,
    Options,
    Trace,
    Patch,
    Invalid,
};

const char Crlf[2] = {'\r','\n'};

extern std::string HttpVersionToStr(HttpVersion version);
extern HttpVersion GetHttpVersion(std::string& str);
extern int SplitHttpOfCRLF(std::string& str, std::vector<std::string>& out, int defaultSize = 64);
extern int SplitStrOfSpace(std::string& str, std::vector<std::string>& out, int defaultSize = 4);
extern uint64_t GetCommomStringLength(const std::string& str1, const std::string& str2);
extern int AppendHead(std::string& str,std::map<std::string,std::string>& heads);
}
}
#endif
