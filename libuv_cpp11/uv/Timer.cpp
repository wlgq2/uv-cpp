/*
   Copyright 2017, object_he@yeah.net  All rights reserved.

   Author: object_he@yeah.net 
    
   Last modified: 2017-8-8
    
   Description: 
*/

#include "Timer.h"

using namespace uv;

Timer::Timer(uv_loop_t* loop,uint64_t timeout,uint64_t repeat,TimerCallback callback)
    :loop(loop),
    handle(new uv_timer_t),
    timeout(timeout),
    repeat(repeat),
    timerCallback(callback)
{
    handle->data = (void*)this;
    ::uv_timer_init(loop, handle);
}

Timer::~Timer()
{
    ::uv_close((uv_handle_t*)handle,
    [](uv_handle_t* handle)
    {
        delete handle;
    });
}

void Timer::start()
{
    ::uv_timer_start(handle, Timer::timerProcess,timeout, repeat);
}

TimerCallback Timer::getTimerCallback()
{
    return timerCallback;
}

void Timer::timerProcess(uv_timer_t* handle)
{
    auto ptr = (Timer*)(handle->data);
    auto callback = ptr->getTimerCallback();
    if(callback)
    {
        callback();
    }
}
