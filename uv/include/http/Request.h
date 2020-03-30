/*
   Copyright © 2017-2020, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net

   Last modified: 2020-3-30

   Description: https://github.com/wlgq2/uv-cpp
*/

#ifndef UV_HTTP_REQUEST_H
#define UV_HTTP_REQUEST_H

#include <map>
#include "HttpVersion.h"

namespace uv
{
namespace http
{

class Request 
{
public:
    enum Methon
    {
        Get, 
        Post, 
        Head, 
        Put, 
        Delete,
        Invalid,
    };
public:
    Request();
    Request(HttpVersion version, Methon methon);

    std::string& getBody();
    void appendParam(std::string& key, std::string& value);

    void setVersion(HttpVersion version);
    void setMethon(Methon methon);
    void setPath(std::string& path);
    std::string& getPath();
    HttpVersion getVersion();
    Methon getMethon();

    int pack(std::string& data);
    int unpack(std::string& data);
private:
    Methon methon_; 
    std::string path_;
    HttpVersion version_;
    std::map<std::string, std::string> params_;
    std::string body_;
};

}
}
#endif
