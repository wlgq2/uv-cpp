/*
   Copyright 2017, object_he@yeah.net  All rights reserved.

   Author: object_he@yeah.net

   Last modified: 2017-11-8

   Description:
*/

#ifndef UV_TCP_CONNECTION_H
#define UV_TCP_CONNECTION_H

#include <iostream>
#include <memory>


#include <chrono>
#include <functional>
#include <atomic>

#include <uv/EventLoop.h>

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


using AfterWriteCallback =  std::function<void (WriteInfo& info)> ;
using OnMessageCallback =  std::function<void (std::shared_ptr<TcpConnection>,const char* buf,ssize_t size)>  ;
using OnConnectCloseCallback =  std::function<void (std::string& )>  ;



class TcpConnection : public std::enable_shared_from_this<TcpConnection>
{

public :
    TcpConnection(EventLoop* loop,std::string& name,uv_tcp_t* client,bool isConnected = true);
    virtual ~TcpConnection();
    void onMessage(const char* buf,ssize_t size);
    void onClose();

    int write(const char* buf,ssize_t size,AfterWriteCallback callback);
    void writeInLoop(const char* buf,ssize_t size,AfterWriteCallback callback);


    void setElement(std::shared_ptr<ConnectionElement> conn);
    std::weak_ptr<ConnectionElement> Element();

    static void  onMesageReceive(uv_stream_t* client, ssize_t nread, const uv_buf_t* buf);

    void setMessageCallback(OnMessageCallback callback)
    {
        onMessageCallback_ = callback;
    }

    void setConnectCloseCallback(OnConnectCloseCallback callback)
    {
        onConnectCloseCallback_ = callback;
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
    uv_tcp_t* client_;

    std::weak_ptr<ConnectionElement> element_;

    OnMessageCallback onMessageCallback_;
    OnConnectCloseCallback onConnectCloseCallback_;

};

}
#endif
