#ifndef ECHOSERVER_HPP
#define ECHOSERVER_HPP

#include <uv/include/uv11.hpp>
#include <atomic>

class EchoServer :public uv::TcpServer
{
public:
    EchoServer(uv::EventLoop* loop);

    uint64_t Cnt();
    void clearCnt();
private :
    std::atomic<uint64_t> cnt;
    void newMessage(uv::TcpConnectionPtr connection,const char* buf,ssize_t size);
};

#endif 
