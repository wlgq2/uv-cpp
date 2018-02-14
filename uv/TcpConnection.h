/*
   Copyright 2017, object_he@yeah.net  All rights reserved.

   Author: object_he@yeah.net

   Last modified: 2017-11-8

   Description:
*/

#ifndef UV_TCP_CONNECTION_H
#define UV_TCP_CONNECTION_H


#include <memory>


#include <chrono>
#include <functional>
#include <atomic>

#include "EventLoop.h"

namespace uv
{

struct WriteInfo
{
	static const int Disconnected = -1;
	int status;
	char* buf;
	unsigned long size;
};


class TcpConnection ;
class TcpServer;
class ConnectionElement;


using AfterWriteCallback =  std::function<void (WriteInfo& )> ;
using OnMessageCallback =  std::function<void (std::shared_ptr<TcpConnection>,const char*,ssize_t)>  ;
using OnCloseCallback =  std::function<void (std::string& )>  ;
using CloseCompleteCallback =  std::function<void (std::string&)>  ;


class TcpConnection : public std::enable_shared_from_this<TcpConnection>
{

public :
    TcpConnection(EventLoop* loop,std::string& name,uv_tcp_t* client,bool isConnected = true);
    virtual ~TcpConnection();
    void onMessage(const char* buf,ssize_t size);
    void onSocketClose();
    void close(std::function<void(std::string&)> callback);
    
    int write(const char* buf,ssize_t size,AfterWriteCallback callback);
    void writeInLoop(const char* buf,ssize_t size,AfterWriteCallback callback);


    void setElement(std::shared_ptr<ConnectionElement> conn);
    std::weak_ptr<ConnectionElement> Element();

    static void  onMesageReceive(uv_stream_t* client, ssize_t nread, const uv_buf_t* buf);

    void setMessageCallback(OnMessageCallback callback)
    {
        onMessageCallback_ = callback;
    }

    void setConnectCloseCallback(OnCloseCallback callback)
    {
        onConnectCloseCallback_ = callback;
    }

    void CloseComplete()
    {
        if(closeCompleteCallback_)
        {
            closeCompleteCallback_(name_);
        }
    }
    void setConnectStatus(bool status)
    {
        connected_ = status;
    }

    bool isConnected()
    {
        return connected_;
    }

    std::string& Name()
    {
        return name_;
    }
private :
    std::string name_;
    bool connected_;
    EventLoop* loop_;
    uv_tcp_t* handle_;

    std::weak_ptr<ConnectionElement> element_;

    OnMessageCallback onMessageCallback_;
    OnCloseCallback onConnectCloseCallback_;
    CloseCompleteCallback closeCompleteCallback_;
    

};

}
#endif
