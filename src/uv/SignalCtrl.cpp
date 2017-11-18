/*
   Copyright 2017, object_he@yeah.net  All rights reserved.

   Author: object_he@yeah.net 
    
   Last modified: 2017-10-9
    
   Description: 
*/

#include <iostream>
#include "uv/SignalCtrl.h"

using namespace uv;
using namespace std;

SignalCtrl::SignalCtrl(EventLoop* loop)
{
    ::uv_signal_init(loop->hanlde(), &signal_);
    signal_.data = static_cast<void*>(this);
}

void SignalCtrl::setHandle(int sig, SignalHandle handle)
{
    auto rst = hanldes_.find(sig);
    if (rst == hanldes_.end())
    {
        ::uv_signal_start(&signal_, &SignalCtrl::onSignal, sig);
        hanldes_.insert(pair<int, SignalHandle>(sig, handle)) ;
    }
    else
    {
        rst->second = handle;
    }
}

bool SignalCtrl::handle(int signum)
{
    auto rst = hanldes_.find(signum);
    if (rst == hanldes_.end())
    {
        rst->second(signum);
        return true;
    }
    return false;
}

void SignalCtrl::onSignal(uv_signal_t* handle, int signum)
{
    auto ptr = static_cast <SignalCtrl*>(handle->data);
    if (!ptr->handle(signum))
    {
        cout << "non defined signal handle :" << signum << endl;
    }
}
