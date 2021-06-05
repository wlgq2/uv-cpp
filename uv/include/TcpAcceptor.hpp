/*
   Copyright © 2017-2019, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net

   Last modified: 2019-12-31

   Description:  https://github.com/wlgq2/uv-cpp
*/

#ifndef     UV_TCP_ACCEPTER_HPP
#define     UV_TCP_ACCEPTER_HPP


#include <functional>

#include "EventLoop.hpp"
#include "SocketAddr.hpp"

namespace uv
{

using NewConnectionCallback  =    std::function<void(EventLoop* ,UVTcpPtr)> ;

class TcpAcceptor
{
public:
    TcpAcceptor(EventLoop* loop, bool tcpNoDelay);

    virtual ~TcpAcceptor();

    int bind(SocketAddr& addr);
    int listen();
    bool isListen();
    void close(DefaultCallback callback);
    bool isTcpNoDelay();
    void setNewConnectionCallback(NewConnectionCallback callback);

    EventLoop* Loop();
    

private:
    bool listened_;
    bool tcpNoDelay_;
    EventLoop* loop_;
    NewConnectionCallback callback_;
    DefaultCallback onCloseCompletCallback_;
    uv_tcp_t server_;

    void onNewConnect(UVTcpPtr client);
    void onCloseComplete();
};

}

#endif
