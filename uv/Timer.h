/*
   Copyright 2017, object_he@yeah.net  All rights reserved.

   Author: object_he@yeah.net 
    
   Last modified: 2017-10-10
    
   Description: 
*/
#ifndef UV_TIMER_H
#define UV_TIMER_H

#include <functional>
#include <mutex>
#include "EventLoop.h"


namespace uv
{
using TimerCloseComplete = std::function<void()>;

template <typename ValueType>
class Timer
{
public:
    using TimerCallback = std::function<void(Timer<ValueType>*,ValueType)>;

    Timer(EventLoop* loop,uint64_t timeout,uint64_t repeat,TimerCallback callback, ValueType value)
        :started_(false),
        handle_(new uv_timer_t),
        timeout_(timeout),
        repeat_(repeat),
        callback_(callback),
        arg_(value),
        closeComplete_(nullptr)
    {
        handle_->data = static_cast<void*>(this);
        ::uv_timer_init(loop->hanlde(), handle_);
    }

    virtual ~Timer()
    {

    }

    void start()
    {
        std::unique_lock<std::mutex> lock(mutex_);
        if (!started_)
        {
            started_ = true;
            ::uv_timer_start(handle_, Timer<ValueType>::process, timeout_, repeat_);
        }
    }
    void close(TimerCloseComplete callback)
    {   
        if (uv_is_active((uv_handle_t*)handle_))
        {
            uv_timer_stop(handle_);
        }
        if (uv_is_closing((uv_handle_t*)handle_) == 0)
        {
            closeComplete_ = callback;
            ::uv_close((uv_handle_t*)handle_,
                [](uv_handle_t* handle)
            {
                auto ptr = static_cast<Timer<ValueType>*>(handle->data);
                ptr->colseComplete();
                delete handle;
            });
        }
        else
        {
            callback();
        }
    }
    TimerCallback Callback()
    {
        return callback_;
    }

    ValueType getArg()
    {
        return arg_;
    };

    void colseComplete()
    {
        if (closeComplete_)
            closeComplete_();
    }
private:
    bool started_;
    uv_timer_t* handle_;
    uint64_t timeout_;
    uint64_t repeat_;
    TimerCallback callback_;
    ValueType arg_;
    std::mutex mutex_;
    TimerCloseComplete closeComplete_;

    static void process(uv_timer_t* handle)
    {
        auto ptr = static_cast<Timer<ValueType>*>(handle->data);
        auto callback = ptr->Callback();
        if (callback)
        {
            callback(ptr,ptr->getArg());
        }
    }

};

}
#endif
