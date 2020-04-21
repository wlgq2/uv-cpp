/*
   Copyright © 2017-2020, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net

   Last modified: 2020-3-30

   Description: https://github.com/wlgq2/uv-cpp
*/

#ifndef UV_HTTP_REQUEST_H
#define UV_HTTP_REQUEST_H

#include <map>
#include "HttpCommon.h"
#include "../GlobalConfig.h"

namespace uv
{
namespace http
{

class Request
{
public:
    Request();
    Request(HttpVersion version, Methon methon);

    void swapContent(std::string& str);
    void swapContent(std::string&& str);
    std::string& getContent();
    void appendHead(std::string& key, std::string& value);
    void appendHead(std::string&& key, std::string&& value);
    std::string getHead(std::string& key);
    std::string getHead(std::string&& key);
    void appendUrlParam(std::string& key, std::string& value);
    void appendUrlParam(std::string&& key, std::string&& value);
    std::string getUrlParam(std::string& key);
    std::string getUrlParam(std::string&& key);

    void setVersion(HttpVersion version);
    void setMethon(Methon methon);
    void setPath(std::string&& path);
    void setPath(std::string& path);
    std::string& getValue();
    std::string& getPath();
    HttpVersion getVersion();
    Methon getMethon();

    int pack(std::string& data);
    ParseResult unpack(std::string& data);
    ParseResult unpackAndCompleted(std::string& data);

    static std::string MethonToStr(Methon methon);
    static Methon StrToMethon(std::string& str);
private:
    HttpVersion version_;
    Methon methon_;
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
