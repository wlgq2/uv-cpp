/*
   Copyright 2017, object_he@yeah.net  All rights reserved.

   Author: object_he@yeah.net 
    
   Last modified: 2017-10-9
    
   Description: 
*/

#include "Signal.h"
#include "LogInterface.h"

using namespace uv;
using namespace std;

Signal::Signal(EventLoop* loop, int sig, SignalHandle handle)
    :signal_(new uv_signal_t),
    hanlde_(handle),
    closeCallback_(nullptr)
{
    ::uv_signal_init(loop->hanlde(), signal_);
    signal_->data = static_cast<void*>(this);
    ::uv_signal_start(signal_, &Signal::onSignal, sig);
}

void uv::Signal::close(std::function<void()>& callback)
{
    closeCallback_ = callback;
    if (uv_is_closing((uv_handle_t*)signal_) == 0)
    {
        ::uv_close((uv_handle_t*)signal_,
            [](uv_handle_t* handle)
        {
            auto ptr = static_cast<Signal*>(handle->data);
            ptr->closeComplete();
            delete handle;
        });
    }
    else
    {
        closeCallback_();
    }
}

Signal::~Signal()
{
}

void Signal::setHandle(SignalHandle handle)
{
    hanlde_ = handle;
}

bool Signal::handle(int signum)
{
    if (hanlde_)
    {
        hanlde_(signum);
        return true;
    }
    return false;
}

void uv::Signal::closeComplete()
{
    if (closeCallback_)
        closeCallback_();
}

int uv::Signal::Ignore(int sig)
{
#ifdef    LINUX
    return signal(sig, SIG_IGN)
#endif
    return 0;
}

void Signal::onSignal(uv_signal_t* handle, int signum)
{
    auto ptr = static_cast <Signal*>(handle->data);
    if (!ptr->handle(signum))
    {
        uv::Log::Instance()->warn( std::string("non defined signal handle :")+std::to_string(signum));
    }
}
