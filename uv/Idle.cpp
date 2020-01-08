/*
   Copyright © 2017-2019, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net
    
   Last modified: 2019-9-10
    
   Description: uv-cpp
*/

#include "include/Idle.h"

using namespace uv;

Idle::Idle(EventLoop* loop)
    :idle_(new uv_idle_t())
{
    idle_->data = this;
    uv_idle_init(loop->handle(), idle_);
    uv_idle_start(idle_, idleCallback);
}

Idle::~Idle()
{
    uv_idle_stop(idle_);
    delete idle_;
}

void  Idle::onCallback()
{
    if (callback_)
        callback_();
}

void  Idle::setCallback(DefaultCallback callback)
{
    callback_ = callback;
}

void  Idle::idleCallback(uv_idle_t* handle)
{
    Idle* ptr = static_cast<Idle*>(handle->data);
    ptr->onCallback();
}
