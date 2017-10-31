/*
   Copyright 2017, object_he@yeah.net  All rights reserved.

   Author: object_he@yeah.net 
    
   Last modified: 2017-10-9
    
   Description: 
*/

#ifndef UV_SIGNAL_CTRL_H
#define UV_SIGNAL_CTRL_H


#include <map>
#include <functional>

#include "uv/EventLoop.h"

namespace uv
{

using SignalHandle = std::function<void(int)>;

class SignalCtrl
{
public:
    SignalCtrl(EventLoop* loop);
    virtual ~SignalCtrl(){}

    void setHandle(int sig, SignalHandle handle);
    bool handle(int signum);
private:
    uv_signal_t signal_;

    std::map<int, SignalHandle> hanldes_;
    static void onSignal(uv_signal_t* handle, int signum);
};

}
#endif
