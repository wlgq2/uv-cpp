/*
   Copyright © 2017-2019, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net

   Last modified: 2019-12-31

   Description: https://github.com/wlgq2/uv-cpp
*/

#ifndef UV_TCP_CONNECTION_H
#define UV_TCP_CONNECTION_H

#include <memory>


#include <chrono>
#include <functional>
#include <atomic>
#include <string>

#include "EventLoop.h"
#include "ListBuffer.h"
#include "CycleBuffer.h"
#include "SocketAddr.h"

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

using TcpConnectionPtr = std::shared_ptr<TcpConnection>;
using AfterWriteCallback =  std::function<void (WriteInfo& )> ;
using OnMessageCallback =  std::function<void (TcpConnectionPtr,const char*,ssize_t)>  ;
using OnCloseCallback =  std::function<void (std::string& )>  ;
using CloseCompleteCallback =  std::function<void (std::string&)>  ;


class TcpConnection : public std::enable_shared_from_this<TcpConnection>
{
public :
    TcpConnection(EventLoop* loop,std::string& name,UVTcpPtr client,bool isConnected = true);
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

    char* resizeData(size_t size);

    PacketBufferPtr getPacketBuffer();

private :
    std::string name_;
    bool connected_;
    EventLoop* loop_;
    UVTcpPtr handle_;
    std::string data_;
    PacketBufferPtr buffer_;
    std::weak_ptr<ConnectionElement> element_;

    OnMessageCallback onMessageCallback_;
    OnCloseCallback onConnectCloseCallback_;
    CloseCompleteCallback closeCompleteCallback_;
};

}
#endif
