/*
   Copyright 2017, object_he@yeah.net  All rights reserved.

   Author: object_he@yeah.net 
    
   Last modified: 2017-8-17
    
   Description: 
*/
#ifndef TIMER_H
#define TIMER_H

#include <functional>
#include <uv.h>


namespace uv
{

typedef std::function<void()> TimerCallback;

class Timer
{
public:
    Timer(uv_loop_t* loop,uint64_t timeout,uint64_t repeat,TimerCallback callback);
    ~Timer();
    void start();
    TimerCallback getTimerCallback();


private:
    uv_loop_t* loop;
    uv_timer_t* handle;
    uint64_t timeout;
    uint64_t repeat;
    TimerCallback timerCallback;
    static void timerProcess(uv_timer_t* handle);
};

}
#endif
