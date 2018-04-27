/*
   Copyright 2017, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net

   Last modified: 2017-11-8

   Description: https://github.com/wlgq2/libuv_cpp11
*/

#ifndef UV_TCP_CONNECTION_H
#define UV_TCP_CONNECTION_H

#define  USE_CYCLE_BUFFER     1

#if     USE_CYCLE_BUFFER
#define     USE_LIST_BUFFER   0
#else
#define     USE_LIST_BUFFER   1
#endif

#include <memory>


#include <chrono>
#include <functional>
#include <atomic>

#include "EventLoop.h"
#include "ListBuffer.h"
#include "CycleBuffer.h"

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

    void setMessageCallback(OnMessageCallback callback);

    void setConnectCloseCallback(OnCloseCallback callback);

    void CloseComplete();

    void setConnectStatus(bool status);

    bool isConnected();
    std::string& Name();

    int appendToBuffer(const char* data, int size);
    int readFromBuffer(Packet& packet);

private :
    std::string name_;
    bool connected_;
    EventLoop* loop_;
    uv_tcp_t* handle_;

#if USE_CYCLE_BUFFER
    ArrayBuffer buffer_;
#endif

#if  USE_LIST_BUFFER
    ListBuffer buffer_;
#endif
    std::weak_ptr<ConnectionElement> element_;

    OnMessageCallback onMessageCallback_;
    OnCloseCallback onConnectCloseCallback_;
    CloseCompleteCallback closeCompleteCallback_;
    

};

}
#endif
