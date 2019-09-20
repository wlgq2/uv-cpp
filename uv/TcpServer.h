/*
   Copyright 2017, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net

   Last modified: 2018-10-9

   Description: https://github.com/wlgq2/uv-cpp
*/

#ifndef UV_TCP_SERVER_H
#define UV_TCP_SERVER_H

#include <functional>
#include <memory>
#include <set>
#include <map>

#include "TcpAccepter.h"
#include "TcpConnection.h"
#include "TimerWheel.h"

namespace uv
{

using OnConnectionStatusCallback =  std::function<void (std::weak_ptr<TcpConnection> )> ;

//no thread safe.
class TcpServer
{
public:
    TcpServer(EventLoop* loop, SocketAddr& addr,bool tcpNoDealy = true);
    virtual ~TcpServer();
    void start();
    void addConnnection(std::string& name,TcpConnectionPtr connection);
    void removeConnnection(std::string& name);
    TcpConnectionPtr getConnnection(std::string& name);
    void closeConnection(std::string& name);

    void onMessage(TcpConnectionPtr connection,const char* buf,ssize_t size);
    void setMessageCallback(OnMessageCallback callback);

    void setNewConnectCallback(OnConnectionStatusCallback callback);
    void setConnectCloseCallback(OnConnectionStatusCallback callback);

    void write(TcpConnectionPtr connection,const char* buf,unsigned int size, AfterWriteCallback callback = nullptr);
    void write(std::string& name,const char* buf,unsigned int size, AfterWriteCallback callback =nullptr);
    void writeInLoop(TcpConnectionPtr connection,const char* buf,unsigned int size,AfterWriteCallback callback);
    void writeInLoop(std::string& name,const char* buf,unsigned int size,AfterWriteCallback callback);

    void setTimeout(unsigned int);

protected:
    EventLoop* loop_;
private:
    SocketAddr::IPV ipv_;
    std::shared_ptr <TcpAccepter> accetper_;
    std::map<std::string ,TcpConnectionPtr>  connnections_;


    OnMessageCallback onMessageCallback_;
    OnConnectionStatusCallback onNewConnectCallback_;
    OnConnectionStatusCallback onConnectCloseCallback_;
    TimerWheel timerWheel_;
    

};


}
#endif
