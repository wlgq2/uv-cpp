/*
Copyright 2017, orcaer@yeah.net  All rights reserved.

Author: orcaer@yeah.net

Last modified: 2019-8-4

Description: https://github.com/wlgq2/uv-cpp
*/
#include "Udp.h"
#include "LogWriter.h"

using namespace uv;

uv::Udp::Udp(EventLoop* loop, SocketAddr& addr)
    :handle_(new uv_udp_t()),
    addr_(addr),
    onMessageCallback_(nullptr)
{
    ::uv_udp_init(loop->hanlde(),handle_);
    handle_->data = this;

    uv_udp_bind(handle_, addr_.Addr(), 0);
}

uv::Udp::~Udp()
{
    delete handle_;
}

void uv::Udp::startRead()
{
    ::uv_udp_recv_start(handle_,
        [](uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf)
    {
        buf->base = new char[suggested_size];
#if _MSC_VER
        buf->len = (ULONG)suggested_size;
#else
        buf->len = suggested_size;
#endif
    },
        &Udp::onMesageReceive);
}

int uv::Udp::send(SocketAddr& to, const char* buf, unsigned size)
{
    uv_udp_send_t* sendHandle = new uv_udp_send_t();
    const uv_buf_t uvbuf = uv_buf_init(const_cast<char*>(buf), size);
    return ::uv_udp_send(sendHandle, handle_, &uvbuf, 1, to.Addr(),
        [](uv_udp_send_t* handle, int status)
    {
        if (status) 
        {
            std::string info("udp send error :");
            info += EventLoop::GetErrorMessage(status);
            uv::LogWriter::Instance()->error(info);
        }
        delete handle;
    });
}

void uv::Udp::close(DefaultCallback callback)
{
    onClose_ = callback;
    if (uv_is_active((uv_handle_t*)handle_))
    {
        uv_udp_recv_stop(handle_);
    }
    if (uv_is_closing((uv_handle_t*)handle_) == 0)
    {
        ::uv_close((uv_handle_t*)handle_, [](uv_handle_t* handle)
        {
            Udp* ptr = static_cast<Udp*>(handle->data);
            ptr->onCloseCompleted();
        });
    }
    else
    {
        onCloseCompleted();
    }

}

void uv::Udp::onCloseCompleted()
{
    if (onClose_)
    {
        onClose_();
    }
}

void uv::Udp::onMessage(const sockaddr* from, const char* data, unsigned size)
{
    if (nullptr != onMessageCallback_)
    {
        SocketAddr addr(from, addr_.Ipv());
        onMessageCallback_(addr, data, size);
    }
}

void uv::Udp::setMessageCallback(OnUdpMessageCallback callback)
{
    onMessageCallback_ = callback;
}

void uv::Udp::onMesageReceive(uv_udp_t* handle, ssize_t nread, const uv_buf_t* buf, const sockaddr* addr, unsigned flags)
{
    if (nread < 0) 
    {
        std::string info("udp read error :");
        info += EventLoop::GetErrorMessage((int)nread);
        uv::LogWriter::Instance()->error(info);
    }
    else if(nread >0)
    {
        Udp* obj = static_cast<Udp*>(handle->data);
        obj->onMessage(addr, buf->base, (unsigned)nread);
    }
    else;

    delete[](buf->base);
}

