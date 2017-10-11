/*
   Copyright 2017, object_he@yeah.net  All rights reserved.

   Author: object_he@yeah.net

   Last modified: 2017-8-17

   Description:
*/

#ifndef PROXY_CONNECTION_H
#define PROXY_CONNECTION_H

#include <iostream>
#include <memory>


#include <chrono>
#include <functional>
#include <atomic>

#include <uv/EventLoop.h>

namespace uv
{
//timeout ctrl.

struct write_req_t
{
    uv_write_t req;
    uv_buf_t buf;
} ;
class TcpConnection ;
class TcpServer;
class ConnectionElement;


using AfterWriteCallback =  std::function<void (char* buf, ssize_t size)> ;
using OnMessageCallback =  std::function<void (std::shared_ptr<TcpConnection>,const char* buf,ssize_t size)>  ;
using OnConnectCloseCallback =  std::function<void (std::string& )>  ;



class TcpConnection : public std::enable_shared_from_this<TcpConnection>
{

public :
    TcpConnection(EventLoop* loop,std::string& name,uv_tcp_t* client,bool isConnected = true);
    virtual ~TcpConnection();
    void onMessage(const char* buf,ssize_t size);
    void onClose();

    int write(const char* buf,unsigned int size,AfterWriteCallback callback);
    void writeInLoop(const char* buf,ssize_t size,AfterWriteCallback callback);


    void setElement(std::shared_ptr<ConnectionElement> conn);
    std::weak_ptr<ConnectionElement> Element();

    static void  onMesageReceive(uv_stream_t* client, ssize_t nread, const uv_buf_t* buf);

    void setMessageCallback(OnMessageCallback callback)
    {
        onMessageCallback = callback;
    }

    void setConnectCloseCallback(OnConnectCloseCallback callback)
    {
        onConnectCloseCallback = callback;
    }

    void setConnectState(bool isConnect)
    {
        connected = isConnect;
    }

    bool getConnnectState()
    {
        return connected;
    }

private :
    std::string name;
    bool connected;
    EventLoop* loop;
    uv_tcp_t* client;

    std::weak_ptr<ConnectionElement> element;

    OnMessageCallback onMessageCallback;
    OnConnectCloseCallback onConnectCloseCallback;

};

}
#endif
