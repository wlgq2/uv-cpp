/*
   Copyright 2017, object_he@yeah.net  All rights reserved.

   Author: object_he@yeah.net

   Last modified: 2017-9-19

   Description:
*/

#ifndef   TCP_CLIENT_H
#define   TCP_CLIENT_H

#include  <functional>
#include  "uv/TcpConnection.h"

namespace uv
{

using ConnectCallback =  std::function<void(bool)>  ;
using NewMessageCallback =  std::function<void(const char* buf,ssize_t size)>  ;
using OnConnectClose =  std::function<void()> ;

class TcpClient
{
public:
    TcpClient(EventLoop* loop);
    ~TcpClient();

    void connect(const char* ip, unsigned short port);

    void onConnect(bool successed);
    void onConnectClose(std::string& name);
    void onMessage(std::shared_ptr<TcpConnection> connection,const char* buf,ssize_t size);

    void write(const char* buf,unsigned int size,AfterWriteCallback callback = nullptr)
    {
        if(tcpConnection)
            tcpConnection->write(buf,size,callback);

    }
    void writeInLoop(const char* buf,unsigned int size,AfterWriteCallback callback)
    {
        if (tcpConnection)
            tcpConnection->writeInLoop(buf,size,callback);
    }

    void setConnectCallback(ConnectCallback callback)
    {
        connectCallback = callback;
    }
    void setMessageCallback(NewMessageCallback callback)
    {
        onMessageCallback = callback;
    }
    void setConnectCloseCallback(OnConnectClose callback)
    {
        onConnectCloseCallback = callback;
    }

protected:
    EventLoop* loop;
private:
    uv_tcp_t* socket;
    uv_connect_t* connect_;
    struct sockaddr_in dest;
    ConnectCallback connectCallback;
    NewMessageCallback onMessageCallback;
    OnConnectClose onConnectCloseCallback;

    std::shared_ptr<TcpConnection> tcpConnection;
    void updata();
};

}
#endif
