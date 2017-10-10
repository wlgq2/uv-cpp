#ifndef ECHOSERVER_H
#define ECHOSERVER_H

#include "uv/TcpServer.h"


class EchoServer :public uv::TcpServer
{
public:
    EchoServer(uv::EventLoop* loop,int port ,const char* ip);
private :
    void newMessage(std::shared_ptr<uv::TcpConnection> connection,const char* buf,ssize_t size);
};

#endif // ECHOSERVER_H
