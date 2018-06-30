/*
   Copyright 2017, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net
    
   Last modified: 2018-4-24
    
   Description: https://github.com/wlgq2/libuv_cpp11
*/
#ifndef UV_TIMER_H
#define UV_TIMER_H

#include <functional>
#include <mutex>
#include "EventLoop.h"


namespace uv
{


template <typename ValueType>
class Timer
{
public:
    using TimerCallback = std::function<void(Timer<ValueType>*,ValueType)>;
    using TimerCloseComplete = std::function<void(Timer<ValueType>*)>;

    Timer(EventLoop* loop, uint64_t timeout, uint64_t repeat, TimerCallback callback, ValueType value);
    virtual ~Timer();

    void start();
    void close(TimerCloseComplete callback);

private:
    bool started_;
    uv_timer_t* handle_;
    uint64_t timeout_;
    uint64_t repeat_;
    TimerCallback callback_;
    ValueType arg_;
    TimerCloseComplete closeComplete_;

private:
    void onTimeOut();
    void colseComplete();

    static void process(uv_timer_t* handle);

};



template<typename ValueType>
inline Timer<ValueType>::Timer(EventLoop * loop, uint64_t timeout, uint64_t repeat, TimerCallback callback, ValueType value)
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

template<typename ValueType>
inline Timer<ValueType>::~Timer()
{
}

template<typename ValueType>
inline void Timer<ValueType>::start()
{
    if (!started_)
    {
        started_ = true;
        ::uv_timer_start(handle_, Timer<ValueType>::process, timeout_, repeat_);
    }
}

template<typename ValueType>
inline void Timer<ValueType>::close(TimerCloseComplete callback)
{
    closeComplete_ = callback;
    if (uv_is_active((uv_handle_t*)handle_))
    {
        uv_timer_stop(handle_);
    }
    if (uv_is_closing((uv_handle_t*)handle_) == 0)
    {
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
        colseComplete();
    }
}

template<typename ValueType>
inline void Timer<ValueType>::onTimeOut()
{
    if (callback_)
    {
        callback_(this, arg_);
    }
}

template<typename ValueType>
inline void Timer<ValueType>::colseComplete()
{
    if (closeComplete_)
        closeComplete_(this);
}

template<typename ValueType>
inline void Timer<ValueType>::process(uv_timer_t * handle)
{
    auto ptr = static_cast<Timer<ValueType>*>(handle->data);
    ptr->onTimeOut();
}
}
#endif
