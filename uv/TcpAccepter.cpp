/*
   Copyright 2017, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net
    
   Last modified: 2017-10-9
    
   Description: https://github.com/wlgq2/libuv_cpp11
*/

#include "TcpAccepter.h"
#include "LogInterface.h"

using namespace std;
using namespace uv;

TcpAccepter::TcpAccepter(EventLoop* loop, SocketAddr& addr, bool tcpNoDelay)
    :listened_(false),
    tcpNoDelay_(tcpNoDelay),
    loop_(loop),
    callback_(nullptr)
{
    ::uv_tcp_init(loop_->hanlde(), &server_);
    if (tcpNoDelay_)
        ::uv_tcp_nodelay(&server_, 1);
    ::uv_tcp_bind(&server_, addr.Addr(),0);
    server_.data = (void* )this;
}



TcpAccepter:: ~TcpAccepter()
{

}

EventLoop* TcpAccepter::Loop()
{
    return loop_;
}

void TcpAccepter::onNewConnect(uv_tcp_t* client)
{
    if(nullptr !=callback_)
    {
        callback_(loop_,client);
    }
}

void TcpAccepter::listen()
{
    ::uv_listen((uv_stream_t*) &server_, 128,
    [](uv_stream_t *server, int status)
    {
        if (status < 0)
        {
            uv::Log::Instance()->error (std::string("New connection error :")+ EventLoop::GetErrorMessage(status));
            return;
        }
        TcpAccepter* accept = static_cast<TcpAccepter*>(server->data);
        uv_tcp_t* client =new uv_tcp_t();
        ::uv_tcp_init(accept->Loop()->hanlde(), client);
        if (accept->isTcpNoDelay())
            ::uv_tcp_nodelay(client, 1);

        if ( 0 == ::uv_accept(server, (uv_stream_t*) client))
        {
            accept->onNewConnect(client);
        }
        else
        {
            ::uv_close((uv_handle_t*) client, NULL);
            delete client;
        }
    });
    listened_ = true;
}


bool TcpAccepter::isListen()
{
    return listened_;
}

bool uv::TcpAccepter::isTcpNoDelay()
{
    return tcpNoDelay_;
}

void TcpAccepter::setNewConnectinonCallback(NewConnectionCallback callback)
{
    callback_ = callback;
}
