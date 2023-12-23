/*
   Copyright © 2017-2020, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net

   Last modified: 2020-3-30

   Description: https://github.com/wlgq2/uv-cpp
*/

#ifndef UV_HTTP_REQUEST_HPP
#define UV_HTTP_REQUEST_HPP

#include <map>
#include "HttpCommon.hpp"
#include "../GlobalConfig.hpp"

namespace uv
{
namespace http
{

class Request
{
public:
    Request(HttpVersion version=HttpVersion::Http1_1, Method method=Method::Get);

    void setVersion(HttpVersion version);
    void setMethod(Method method);
    HttpVersion getVersion();
    Method getMethod();

    void swapContent(std::string& str);
    void swapContent(std::string&& str);
    const std::string& getContent();
    void appendHead(std::string& key, std::string& value);
    void appendHead(std::string&& key, std::string&& value);
    std::string getHead(std::string& key);
    std::string getHead(std::string&& key);
    void appendUrlParam(std::string& key, std::string& value);
    void appendUrlParam(std::string&& key, std::string&& value);
    std::string getUrlParam(std::string& key);
    std::string getUrlParam(std::string&& key);

    void setPath(std::string&& path);
    void setPath(std::string& path);
    const std::string& getPath();
    const std::string& getValue();

    int pack(std::string& data);
    ParseResult unpack(std::string& data);
    ParseResult unpackAndCompleted(std::string& data);

    static std::string MethodToStr(Method method);
    static Method StrToMethod(std::string& str);
private:
    HttpVersion version_;
    Method method_;
    std::string path_;
    std::string value_;
    std::map <std::string, std::string> urlParms_;
    std::map<std::string, std::string> heads_;
    std::string content_;

    void packPathParam(std::string& path);
    int unpackUrl(std::string& str);
    int unpackPath(std::string& str);
};

}
}
#endif
