/*
   Copyright 2017, object_he@yeah.net  All rights reserved.

   Author: object_he@yeah.net 
    
   Last modified: 2017-8-8
    
   Description: 
*/

#ifndef     TCP_ACCEPTER_H
#define     TCP_ACCEPTER_H


#include <functional>

#include "uv/EventLoop.h"
#include "uv/SocketAddr.h"

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

    EventLoop* getLoop();
    void onNewConnect(uv_tcp_t* client);

private:
    bool listened;
    EventLoop* loop;
    NewConnectionCallback newConnectionCallback;

    uv_tcp_t server;

};

}

#endif
