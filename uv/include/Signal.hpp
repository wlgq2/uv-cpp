/*
   Copyright © 2017-2019, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net
    
   Last modified: 2018-8-23
    
   Description:  https://github.com/wlgq2/uv-cpp
*/

#ifndef UV_SIGNAL_HPP
#define UV_SIGNAL_HPP


#include <map>
#include <functional>

#include "EventLoop.hpp"

namespace uv
{

using SignalHandle = std::function<void(int)>;

class Signal
{
public:
    Signal(EventLoop* loop,int sig, SignalHandle handle = nullptr);
    void close(DefaultCallback callback);
    virtual ~Signal();

    void setHandle(SignalHandle handle);
    static void Ignore(int sig);
private:
    uv_signal_t* signal_;
    SignalHandle handle_;
    DefaultCallback closeCallback_;

    bool handle(int signum);
    void closeComplete();
    static void onSignal(uv_signal_t* handle, int signum);
};

}
#endif
