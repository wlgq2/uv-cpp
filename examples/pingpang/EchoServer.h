#ifndef ECHOSERVER_H
#define ECHOSERVER_H

#include "uv/uv11.h"
#include <atomic>
#include "ModeDefine.h"

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

#endif // ECHOSERVER_H
