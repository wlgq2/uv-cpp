/*
   Copyright © 2017-2019, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net
    
   Last modified: 2019-9-11
    
   Description: https://github.com/wlgq2/uv-cpp
*/
#ifndef UV_TIMER_H
#define UV_TIMER_H

#include <functional>
#include <mutex>
#include "EventLoop.h"
namespace uv
{

class Timer
{
public:
    using TimerCallback = std::function<void(Timer* ptr)>;
    using TimerCloseComplete = std::function<void(Timer* ptr)>;

    Timer(EventLoop* loop, uint64_t timeout, uint64_t repeat, TimerCallback callback);
    virtual ~Timer();

    void start();
    void close(TimerCloseComplete callback);
    void setTimerRepeat(uint64_t ms);

private:
    bool started_;
    uv_timer_t* handle_;
    uint64_t timeout_;
    uint64_t repeat_;
    TimerCallback callback_;

    TimerCloseComplete closeComplete_;

private:
    void onTimeOut();
    void closeComplete();

    static void process(uv_timer_t* handle);

};

}
#endif
