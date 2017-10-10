/*
   Copyright 2017, object_he@yeah.net  All rights reserved.

   Author: object_he@yeah.net

   Last modified: 2017-8-14

   Description:
*/

#ifndef PT_SERVER_H
#define PT_SERVER_H

#include <iostream>
#include <functional>
#include <memory>
#include <set>
#include <map>

#include "uv/TcpAccepter.h"
#include "uv/TcpConnection.h"
#include "uv/TimerWheel.h"
#include "uv/EventLoop.h"

namespace uv
{

using OnNewConnectCallback =  std::function<void (std::weak_ptr<TcpConnection> )> ;

//no thread safe.
class TcpServer
{
public:
    TcpServer(EventLoop* loop,int port ,const char* ip = (char*)"0.0.0.0");
    virtual ~TcpServer();
    void start();

    void addConnnection(std::string& name,std::shared_ptr<TcpConnection> connection);
    void removeConnnection(std::string& name);
    std::shared_ptr<TcpConnection> getConnnection(std::string& name);
    void closeConnection(std::string& name);

    void onMessage(std::shared_ptr<TcpConnection> connection,const char* buf,ssize_t size);
    void setMessageCallback(OnMessageCallback callback);

    void setNewConnectCallback(OnNewConnectCallback callback);

    void write(std::shared_ptr<TcpConnection> connection,const char* buf,unsigned int size);
    void write(std::string& name,const char* buf,unsigned int size);
    void writeInLoop(std::shared_ptr<TcpConnection> connection,const char* buf,unsigned int size,AfterWriteCallback callback);
    void writeInLoop(std::string& name,const char* buf,unsigned int size,AfterWriteCallback callback);

    void setTimeout(unsigned int);

protected:
    EventLoop* loop;
private:
    std::shared_ptr <TcpAccepter> accetper;
    std::map<std::string ,std::shared_ptr<TcpConnection>>  connnections;


    OnMessageCallback onMessageCallback;
    OnNewConnectCallback onNewConnectCallback;
    TimerWheel timerWheel;

};


}
#endif
