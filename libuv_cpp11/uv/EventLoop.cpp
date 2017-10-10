/*
   Copyright 2017, object_he@yeah.net  All rights reserved.

   Author: object_he@yeah.net 
    
   Last modified: 2017-10-10
    
   Description: 
*/

#include "uv/EventLoop.h"

using namespace uv;

EventLoop::EventLoop(EventLoop::Mode mode)
{
    if (mode == EventLoop::DefaultLoop)
    {
        loop = uv_default_loop();
    }
    else
    {
        loop = new uv_loop_t();
        uv_loop_init(loop);
    }
}

EventLoop::~EventLoop()
{
    if (loop != uv_default_loop())
    {
        delete loop;
    }
}

uv_loop_t* EventLoop::hanlde()
{
    return loop;
}

int EventLoop::run()
{
    return ::uv_run(loop, UV_RUN_DEFAULT);
}