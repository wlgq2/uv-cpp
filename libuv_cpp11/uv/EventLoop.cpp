/*
   Copyright 2017, object_he@yeah.net  All rights reserved.

   Author: object_he@yeah.net 
    
   Last modified: 2017-10-10
    
   Description: 
*/

#include "uv/EventLoop.h"

using namespace uv;

EventLoop::EventLoop(EventLoop::Mode mode)
    :isRun(false)
{
    if (mode == EventLoop::NewLoop)
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
        delete loop_;
    }
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


bool EventLoop::isRunInLoopThread()
{
    if (isRun)
    {
        return std::this_thread::get_id() == loopThreadId_;
    }
    //EventLoopŒ¥‘À––.
    return false;
}