/*
   Copyright © 2017-2019, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net

   Last modified: 2019-12-31

   Description:  https://github.com/wlgq2/uv-cpp
*/

#ifndef     UV_TCP_ACCEPTER_H
#define     UV_TCP_ACCEPTER_H


#include <functional>

#include "EventLoop.h"
#include "SocketAddr.h"

namespace uv
{

using NewConnectionCallback  =    std::function<void(EventLoop* ,UVTcpPtr)> ;

class TcpAccepter
{
public:
    TcpAccepter(EventLoop* loop, bool tcpNoDelay);

    virtual ~TcpAccepter();

    int bind(SocketAddr& addr);
    int listen();
    bool isListen();
    bool isTcpNoDelay();
    void setNewConnectinonCallback( NewConnectionCallback callback);

    EventLoop* Loop();
    void onNewConnect(UVTcpPtr client);

private:
    bool listened_;
    bool tcpNoDelay_;
    EventLoop* loop_;
    NewConnectionCallback callback_;

    uv_tcp_t server_;

};

}

#endif
