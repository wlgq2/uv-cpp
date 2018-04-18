/*
   Copyright 2017, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net
    
   Last modified: 2017-8-8
    
   Description:  https://github.com/wlgq2/libuv_cpp11
*/

#ifndef     UV_TCP_ACCEPTER_H
#define     UV_TCP_ACCEPTER_H


#include <functional>

#include "EventLoop.h"
#include "SocketAddr.h"

namespace uv
{

using NewConnectionCallback  =    std::function<void(EventLoop* ,uv_tcp_t*)> ;

class TcpAccepter
{
public:
    TcpAccepter(EventLoop* loop, SocketAddr& addr);
    virtual ~TcpAccepter();

    void listen();
    bool isListen();
    void setNewConnectinonCallback( NewConnectionCallback callback);

    EventLoop* Loop();
    void onNewConnect(uv_tcp_t* client);

private:
    bool listened_;
    EventLoop* loop_;
    NewConnectionCallback callback_;

    uv_tcp_t server_;

};

}

#endif
