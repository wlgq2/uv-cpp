/*
   Copyright © 2017-2020, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net

   Last modified: 2019-12-31

   Description: https://github.com/wlgq2/uv-cpp
*/

#include "include/TcpAccepter.hpp"
#include "include/LogWriter.hpp"

using namespace std;
using namespace uv;

TcpAccepter::TcpAccepter(EventLoop* loop, bool tcpNoDelay)
    :listened_(false),
    tcpNoDelay_(tcpNoDelay),
    loop_(loop),
    callback_(nullptr),
    onCloseCompletCallback_(nullptr)
{
    ::uv_tcp_init(loop_->handle(), &server_);
    if (tcpNoDelay_)
        ::uv_tcp_nodelay(&server_, 1);
    server_.data = (void* )this;
}



TcpAccepter:: ~TcpAccepter()
{

}

EventLoop* TcpAccepter::Loop()
{
    return loop_;
}

void TcpAccepter::onNewConnect(UVTcpPtr client)
{
    if(nullptr !=callback_)
    {
        callback_(loop_,client);
    }
}

void uv::TcpAccepter::onCloseComlet()
{
    if (onCloseCompletCallback_)
        onCloseCompletCallback_();
}

int uv::TcpAccepter::bind(SocketAddr& addr)
{
    return ::uv_tcp_bind(&server_, addr.Addr(), 0);
}

int TcpAccepter::listen()
{
    auto rst = ::uv_listen((uv_stream_t*) &server_, 128,
    [](uv_stream_t *server, int status)
    {
        if (status < 0)
        {
            uv::LogWriter::Instance()->error (std::string("New connection error :")+ EventLoop::GetErrorMessage(status));
            return;
        }
        TcpAccepter* accept = static_cast<TcpAccepter*>(server->data);
        UVTcpPtr client = make_shared<uv_tcp_t>();
        ::uv_tcp_init(accept->Loop()->handle(), client.get());
        if (accept->isTcpNoDelay())
            ::uv_tcp_nodelay(client.get(), 1);

        if ( 0 == ::uv_accept(server, (uv_stream_t*) client.get()))
        {
            accept->onNewConnect(client);
        }
        else
        {
            ::uv_close((uv_handle_t*) client.get(), NULL);
        }
    });
    if (rst == 0)
    {
        listened_ = true;
    }
    return rst;
}


bool TcpAccepter::isListen()
{
    return listened_;
}

void uv::TcpAccepter::close(DefaultCallback callback)
{
    onCloseCompletCallback_ = callback;
    auto ptr = &server_;
    if (::uv_is_active((uv_handle_t*)ptr))
    {
        ::uv_read_stop((uv_stream_t*)ptr);
    }
    if (::uv_is_closing((uv_handle_t*)ptr) == 0)
    {
        //libuv 在loop轮询中会检测关闭句柄，delete会导致程序异常退出。
        ::uv_close((uv_handle_t*)ptr,
            [](uv_handle_t* handle)
        {
            auto accept = static_cast<TcpAccepter*>(handle->data);
            accept->onCloseComlet();
        });
    }
    else
    {
        onCloseComlet();
    }
}

bool uv::TcpAccepter::isTcpNoDelay()
{
    return tcpNoDelay_;
}

void TcpAccepter::setNewConnectinonCallback(NewConnectionCallback callback)
{
    callback_ = callback;
}
