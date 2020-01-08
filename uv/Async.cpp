/*
Copyright © 2017-2019, orcaer@yeah.net  All rights reserved.

Author: orcaer@yeah.net

Last modified: 2019-2-21

Description: https://github.com/wlgq2/uv-cpp
*/
#include "include/Async.h"

using namespace uv;

Async::Async(EventLoop * loop)
    : handle_(new uv_async_t)
{
    ::uv_async_init(loop->handle(), handle_, Async::Callback);
    handle_->data = static_cast<void*>(this);
}

Async::~Async()
{

}

void Async::runInThisLoop(AsyncCallback callback)
{
    {
        std::lock_guard<std::mutex> lock(mutex_);
        callbacks_.push(callback);
    }
    ::uv_async_send(handle_);
}

void uv::Async::process()
{
    std::lock_guard<std::mutex> lock(mutex_);
    while (!callbacks_.empty())
    {
        auto func = callbacks_.front();
        func();
        callbacks_.pop();
    }
}

void uv::Async::close(AsyncCallback callback)
{
    if (::uv_is_closing((uv_handle_t*)handle_) == 0)
    {
        ::uv_close((uv_handle_t*)handle_, [](uv_handle_t* handle)
        {
            delete (uv_async_t*)handle;
        });
    }
}

void Async::Callback(uv_async_t* handle)
{
    auto async = static_cast<Async*>(handle->data);
    async->process();
}