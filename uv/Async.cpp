/*
Copyright © 2017-2020, orcaer@yeah.net  All rights reserved.

Author: orcaer@yeah.net

Last modified: 2020-10-6

Description: https://github.com/wlgq2/uv-cpp
*/
#include "include/Async.hpp"

using namespace uv;

Async::Async(EventLoop * loop)
    :loop_(loop),
    handle_(nullptr),
    onCloseCompletCallback_(nullptr)
{

}

void Async::init()
{
    if (nullptr == handle_)
    {
        handle_ = new uv_async_t;
        ::uv_async_init(loop_->handle(), handle_, Async::Callback);
        handle_->data = static_cast<void*>(this);
        ::uv_async_send(handle_);
    }
}

Async::~Async()
{

}

void Async::runInThisLoop(DefaultCallback callback)
{
    {
        std::lock_guard<std::mutex> lock(mutex_);
        callbacks_.push(callback);
    }
    if(handle_ != nullptr)
        ::uv_async_send(handle_);
}

void uv::Async::process()
{
    std::queue<DefaultCallback> callbacks;
    {
        std::lock_guard<std::mutex> lock(mutex_);
        callbacks_.swap(callbacks);
    }
    while (!callbacks.empty())
    {
        auto func = callbacks.front();
        func();
        callbacks.pop();
    }
}

void Async::close(uv::Async::OnCloseCompletedCallback callback)
{
    onCloseCompletCallback_ = callback;
    if (::uv_is_closing((uv_handle_t*)handle_) == 0)
    {
        ::uv_close((uv_handle_t*)handle_, [](uv_handle_t* handle)
        {
            auto ptr = static_cast<Async*>(handle->data);
            ptr->onCloseCompleted();
            delete (uv_async_t*)handle;
        });
    }
}

EventLoop* uv::Async::Loop()
{
    return loop_;
}

void Async::Callback(uv_async_t* handle)
{
    auto async = static_cast<Async*>(handle->data);
    async->process();
}

void uv::Async::onCloseCompleted()
{
    if (nullptr != onCloseCompletCallback_)
    {
        onCloseCompletCallback_(this);
    }
}
