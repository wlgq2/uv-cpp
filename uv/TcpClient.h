/*
   Copyright 2017, object_he@yeah.net  All rights reserved.

   Author: object_he@yeah.net

   Last modified: 2017-9-19

   Description:
*/

#ifndef   UV_TCP_CLIENT_H
#define   UV_TCP_CLIENT_H

#include  <functional>
#include  <memory>

#include  "TcpConnection.h"
#include  "SocketAddr.h"

namespace uv
{

using ConnectCallback =  std::function<void(bool)>  ;
using NewMessageCallback =  std::function<void(const char*,ssize_t)>  ;
using OnConnectClose =  std::function<void()> ;

class TcpClient
{
public:
    TcpClient(EventLoop* loop);
    virtual ~TcpClient();

    void connect(SocketAddr& addr);

    void onConnect(bool successed);
    void onConnectClose(std::string& name);
    void onMessage(std::shared_ptr<TcpConnection> connection,const char* buf,ssize_t size);
    void close(std::function<void(std::string&)> callback);
    void write(const char* buf,unsigned int size,AfterWriteCallback callback = nullptr)
    {
        if(connection_)
            connection_->write(buf,size,callback);

    }
    void writeInLoop(const char* buf,unsigned int size,AfterWriteCallback callback)
    {
        if (connection_)
            connection_->writeInLoop(buf,size,callback);
    }

    void setConnectCallback(ConnectCallback callback)
    {
        connectCallback_ = callback;
    }
    void setMessageCallback(NewMessageCallback callback)
    {
        onMessageCallback_ = callback;
    }
    void setConnectCloseCallback(OnConnectClose callback)
    {
        onConnectCloseCallback_ = callback;
    }

    EventLoop* Loop()
    {
        return loop_;
    }
protected:
    EventLoop* loop_;
private:
    uv_tcp_t* socket_;
    uv_connect_t* connect_;
    SocketAddr::IPV ipv;

    ConnectCallback connectCallback_;
    NewMessageCallback onMessageCallback_;
    OnConnectClose onConnectCloseCallback_;

    std::shared_ptr<TcpConnection> connection_;
    void updata();
};

using TcpClientPtr = std::shared_ptr<uv::TcpClient>;
}
#endif
