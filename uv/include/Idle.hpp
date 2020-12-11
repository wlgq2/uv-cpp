/*
   Copyright © 2017-2019, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net
    
   Last modified: 2019-9-11
    
   Description: https://github.com/wlgq2/uv-cpp
*/

#ifndef  UV_IDLE_HPP
#define  UV_IDLE_HPP

#include  "EventLoop.hpp"

namespace uv
{

class Idle
{
public:
    Idle(EventLoop* loop);
    virtual ~Idle();

    
    void setCallback(DefaultCallback callback);

private:
    uv_idle_t* idle_;
	
    DefaultCallback callback_;

private:
    void onCallback();
    static void idleCallback(uv_idle_t *handle);
};

}
#endif
