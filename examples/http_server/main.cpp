#include <iostream>
#include <uv/include/uv11.h>

void func1(uv::http::Request& req, uv::http::Response* resp)
{

}

void func2(uv::http::Request& req, uv::http::Response* resp)
{

}
void func3(uv::http::Request& req, uv::http::Response* resp)
{

}
void func4(uv::http::Request& req, uv::http::Response* resp)
{

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
    //example:  127.0.0.1:10010/value1:1234
    server.Get("/value1:",std::bind(&func3, std::placeholders::_1, std::placeholders::_2));
    //example:  127.0.0.1:10010/param?param1=test1&param2=test2
    server.Get("/param",std::bind(&func4, std::placeholders::_1, std::placeholders::_2));

    uv::SocketAddr addr("127.0.0.1", 10010);
    server.bindAndListen(addr);
    loop.run();
}
