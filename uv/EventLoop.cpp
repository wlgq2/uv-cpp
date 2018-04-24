/*
   Copyright 2017, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net
    
   Last modified: 2018-4-18
    
   Description: https://github.com/wlgq2/libuv_cpp11
*/

#include "EventLoop.h"
#include "TcpConnection.h"
#include "Async.h"

using namespace uv;

EventLoop::EventLoop()
    :isRun(false)
{
    loop_ = new uv_loop_t();
    ::uv_loop_init(loop_);
}

EventLoop::EventLoop(EventLoop::Mode mode)
    :isRun(false)
{
    if (mode == EventLoop::New)
    {
        loop_ = new uv_loop_t();
        ::uv_loop_init(loop_);
    }
    else
    {
        loop_ = uv_default_loop();
    }
}

EventLoop::~EventLoop()
{
    if (loop_ != uv_default_loop())
    {
        uv_loop_close(loop_);
        delete loop_;
    }
}

EventLoop* uv::EventLoop::DefalutLoop()
{
    static EventLoop* defaultLoop = new uv::EventLoop(uv::EventLoop::Mode::Default);
    return defaultLoop;
}

uv_loop_t* EventLoop::hanlde()
{
    return loop_;
}

int EventLoop::run()
{
    loopThreadId_ = std::this_thread::get_id();
    isRun = true;
    return ::uv_run(loop_, UV_RUN_DEFAULT);
}

int uv::EventLoop::runNoWait()
{
    loopThreadId_ = std::this_thread::get_id();
    isRun = true;
    return ::uv_run(loop_, UV_RUN_NOWAIT);
}


bool EventLoop::isRunInLoopThread()
{
    if (isRun)
    {
        return std::this_thread::get_id() == loopThreadId_;
    }
    //EventLoopŒ¥‘À––.
    return false;
}

void uv::EventLoop::runInThisLoop(const std::function<void()>& func)
{
    if (nullptr == func)
        return;

    if (isRunInLoopThread())
    {
        func();
        return;
    }
    std::function<void()>* funcptr = new std::function<void()>();
    *funcptr = func;
    uv::Async<std::function<void()>*>* handle = new uv::Async<std::function<void()>*>(this,
        [this](uv::Async<std::function<void()>*>* handle, std::function<void()>* funcptr)
    {
        (*funcptr)();
        delete funcptr;
        delete handle;
    }, funcptr);
    handle->runInLoop();
}

const char* EventLoop::GetErrorMessage(int status)
{
    if (WriteInfo::Disconnected == status)
    {
        static char info[] = "the connection is disconnected";
        return info;
    }
    return uv_strerror(status);
}