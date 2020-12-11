/*
   Copyright © 2017-2020, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net

   Last modified: 2020-3-30

   Description: https://github.com/wlgq2/uv-cpp
*/

#ifndef UV_HTTP_RESPONSE_HPP
#define UV_HTTP_RESPONSE_HPP

#include <map>
#include "HttpCommon.hpp"

namespace uv
{
namespace http
{

class Response 
{
public:
    enum StatusCode
    {
        OK =200,    //客户端请求成功
        BadRequest = 400,  //客户端请求有语法错误，不能被服务器所理解
        Unauthorized  = 401,//请求未经授权，这个状态代码必须和WWW-Authenticate报头域一起使用 
        Forbidden = 403 , //服务器收到请求，但是拒绝提供服务
        NotFound = 404 , //请求资源不存在，eg：输入了错误的URL
        InternalServerError = 500 , //服务器发生不可预期的错误
        ServerUnavailable = 503,  //服务器当前不能处理客户端的请求，一段时间后可能恢复正常
    };

public:
    Response();
    Response(HttpVersion version, StatusCode code);

    void setVersion(HttpVersion version);
    void setStatus(StatusCode code,std::string info);
    HttpVersion getVersion();
    StatusCode getStatusCode();
    const std::string& getStatusInfo();

    void appendHead(std::string& key, std::string& value);
    void appendHead(std::string&& key, std::string&& value);
    
    std::string getHead(std::string& key);
    void swapContent(std::string& body);
    void swapContent(std::string&& body);
    const std::string& getContent();

    int pack(std::string& data);
    ParseResult unpack(std::string& data);
    ParseResult unpackAndCompleted(std::string& data);
    ParseResult isCompletedChunked();

private:
    HttpVersion version_;
    StatusCode statusCode_;
    std::string statusInfo_;
    std::map<std::string, std::string> heads_;
    std::string content_;

    int parseStatus(std::string& str);
};

}
}
#endif
