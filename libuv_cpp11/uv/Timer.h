/*
   Copyright 2017, object_he@yeah.net  All rights reserved.

   Author: object_he@yeah.net 
    
   Last modified: 2017-10-10
    
   Description: 
*/
#ifndef TIMER_H
#define TIMER_H

#include <functional>
#include <uv.h>


namespace uv
{



template <typename ValueType>
class Timer
{
public:
    using TimerCallback = std::function<void(ValueType)>;

    Timer(uv_loop_t* loop,uint64_t timeout,uint64_t repeat,TimerCallback callback, ValueType value)
        :loop(loop),
        handle(new uv_timer_t),
        timeout(timeout),
        repeat(repeat),
        timerCallback(callback),
        arg(value)
    {
        handle->data = static_cast<void*>(this);
        ::uv_timer_init(loop, handle);
    }

    ~Timer()
    {
        ::uv_close((uv_handle_t*)handle,
            [](uv_handle_t* handle)
        {
            delete handle;
        });
    }

    void start()
    {
        ::uv_timer_start(handle, Timer<ValueType>::timerProcess, timeout, repeat);
    }

    TimerCallback getTimerCallback()
    {
        return timerCallback;
    }

    ValueType getArg()
    {
        return arg;
    };
private:
    uv_loop_t* loop;
    uv_timer_t* handle;
    uint64_t timeout;
    uint64_t repeat;
    TimerCallback timerCallback;
    ValueType arg;


    static void timerProcess(uv_timer_t* handle)
    {
        auto ptr = static_cast<Timer<ValueType>*>(handle->data);
        auto callback = ptr->getTimerCallback();
        if (callback)
        {
            callback(ptr->getArg());
        }
    }

};

}
#endif
