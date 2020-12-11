/*
   Copyright © 2017-2020, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net

   Last modified: 2020-4-13

   Description: https://github.com/wlgq2/uv-cpp
*/

#include <iostream>
#include <uv/include/uv11.hpp>

void func1(uv::http::Request& req, uv::http::Response* resp)
{
    resp->setVersion(uv::http::HttpVersion::Http1_1);
    resp->setStatus(uv::http::Response::StatusCode::OK, "OK");
    resp->appendHead("Server", "uv-cpp");
    std::string str("test~");
    resp->swapContent(str);
}

void func2(uv::http::Request& req, uv::http::Response* resp)
{
    resp->setVersion(uv::http::HttpVersion::Http1_1);
    resp->setStatus(uv::http::Response::StatusCode::OK, "OK");
    resp->appendHead("Server", "uv-cpp");
    std::string str = req.getPath();
    resp->swapContent(str);
}
void func3(uv::http::Request& req, uv::http::Response* resp)
{
    resp->setVersion(uv::http::HttpVersion::Http1_1);
    resp->setStatus(uv::http::Response::StatusCode::OK, "OK");
    resp->appendHead("Server", "uv-cpp");
    std::string str("value is ");
    str += req.getValue();
    resp->swapContent(str);
}
void func4(uv::http::Request& req, uv::http::Response* resp)
{
    resp->setVersion(uv::http::HttpVersion::Http1_1);
    resp->setStatus(uv::http::Response::StatusCode::OK, "OK");
    resp->appendHead("Server", "uv-cpp");
    std::string value1 = req.getUrlParam("param1");
    std::string value2 = req.getUrlParam("param2");
    std::string str;
    try 
    {
        double num1 = std::stoi(value1);
        double num2 = std::stoi(value2);
        str = "sum :";
        str += std::to_string(num1 + num2);
    }
    catch (...)
    {
        str = "param is not num.";
    }
    resp->swapContent(str);
}

void func5(uv::http::Request& req, uv::http::Response* resp)
{
    resp->setVersion(uv::http::HttpVersion::Http1_1);
    resp->setStatus(uv::http::Response::StatusCode::OK, "OK");
    resp->appendHead("Server", "uv-cpp");
    std::string str("uv-cpp default page.");
    resp->swapContent(str);
}

int main(int argc, char** args)
{
    uv::EventLoop loop;
    uv::http::HttpServer::SetBufferMode(uv::GlobalConfig::BufferMode::CycleBuffer);

    uv::http::HttpServer server(&loop);
    //example:  127.0.0.1:10010/test
    server.Get("/test",std::bind(&func1,std::placeholders::_1,std::placeholders::_2));
    //example:  127.0.0.1:10010/some123abc
    server.Get("/some*",std::bind(&func2, std::placeholders::_1, std::placeholders::_2));
    //example:  127.0.0.1:10010/value:1234
    server.Get("/value:",std::bind(&func3, std::placeholders::_1, std::placeholders::_2));
    //example:  127.0.0.1:10010/sum?param1=100&param2=23
    server.Get("/sum",std::bind(&func4, std::placeholders::_1, std::placeholders::_2));
    //defalut server.
    server.Get("/*", std::bind(&func5, std::placeholders::_1, std::placeholders::_2));

    uv::SocketAddr addr("127.0.0.1", 10010);
    server.bindAndListen(addr);
    loop.run();
}
