/*
   Copyright 2017, object_he@yeah.net  All rights reserved.

   Author: object_he@yeah.net 
    
   Last modified: 2017-10-10
    
   Description: 
*/
#ifndef UV_TIMER_H
#define UV_TIMER_H

#include <functional>
#include "uv/EventLoop.h"


namespace uv
{



template <typename ValueType>
class Timer
{
public:
    using TimerCallback = std::function<void(ValueType)>;

    Timer(EventLoop* loop,uint64_t timeout,uint64_t repeat,TimerCallback callback, ValueType value)
        :handle_(new uv_timer_t),
        timeout_(timeout),
        repeat_(repeat),
        callback_(callback),
        arg_(value)
    {
        handle_->data = static_cast<void*>(this);
        ::uv_timer_init(loop->hanlde(), handle_);
    }

    virtual ~Timer()
    {
        ::uv_close((uv_handle_t*)handle_,
            [](uv_handle_t* handle)
        {
            delete handle;
        });
    }

    void start()
    {
        ::uv_timer_start(handle_, Timer<ValueType>::process, timeout_, repeat_);
    }

    TimerCallback Callback()
    {
        return callback_;
    }

    ValueType getArg()
    {
        return arg_;
    };
private:
    uv_timer_t* handle_;
    uint64_t timeout_;
    uint64_t repeat_;
    TimerCallback callback_;
    ValueType arg_;


    static void process(uv_timer_t* handle)
    {
        auto ptr = static_cast<Timer<ValueType>*>(handle->data);
        auto callback = ptr->Callback();
        if (callback)
        {
            callback(ptr->getArg());
        }
    }

};

}
#endif
