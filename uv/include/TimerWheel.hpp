/*
   Copyright © 2017-2019, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net
    
   Last modified: 2020-7-21
    
   Description: https://github.com/wlgq2/uv-cpp
*/

#ifndef   UV_TIMER_WHEEL_HPP
#define   UV_TIMER_WHEEL_HPP

#include <vector>
#include <set>
#include <memory>
#include "Timer.hpp"
#include "TcpConnection.hpp"

namespace uv
{

//algorithm complexity  o(1).

template<typename Type>
class TimerWheel
{
public:
    TimerWheel(EventLoop* loop);
    TimerWheel(EventLoop* loop,unsigned int timeout);
    void setTimeout(unsigned int seconds);
    int getTimeout();
    void start();
    void insert(std::shared_ptr<Type> value);
    
private:
    unsigned int index_;
    unsigned int timeoutSec_;
    Timer timer_;

    std::vector<std::set<std::shared_ptr<Type>>> wheel_;

    void wheelCallback();

};

template<typename Type>
inline TimerWheel<Type>::TimerWheel(EventLoop* loop)
    :TimerWheel(loop, 0)
{

}

template<typename Type>
inline TimerWheel<Type>::TimerWheel(EventLoop* loop, unsigned int timeout)
    :index_(0),
    timeoutSec_(timeout),
    timer_(loop, 1000, 1000, std::bind(&TimerWheel::wheelCallback, this))
{

}

template<typename Type>
inline void TimerWheel<Type>::setTimeout(unsigned int seconds)
{
    timeoutSec_ = seconds;
}

template<typename Type>
inline void TimerWheel<Type>::start()
{
    if (timeoutSec_)
    {
        wheel_.resize(timeoutSec_);
        timer_.start();
    }
}

template<typename Type>
inline void TimerWheel<Type>::insert(std::shared_ptr<Type> value)
{
    if (timeoutSec_ > 0 && nullptr != value)
    {
        wheel_[index_].insert(value);
    }
}

template<typename Type>
inline int TimerWheel<Type>::getTimeout()
{
    return timeoutSec_;
}

template<typename Type>
inline void TimerWheel<Type>::wheelCallback()
{
    if (!timeoutSec_)
        return;
    if (++index_ == timeoutSec_)
    {
        index_ = 0;
    }
    wheel_[index_].clear();
}
}
#endif
