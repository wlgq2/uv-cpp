/*
   Copyright 2017, object_he@yeah.net  All rights reserved.

   Author: object_he@yeah.net 
    
   Last modified: 2017-10-9
    
   Description: 
*/

#include <iostream>
#include "SignalCtrl.h"

using namespace uv;
using namespace std;

SignalCtrl::SignalCtrl(uv_loop_t* loop)
{
    ::uv_signal_init(loop, &signal);
    signal.data = static_cast<void*>(this);
}

void SignalCtrl::setHandle(int sig, SignalHandle handle)
{
    auto rst = hanldes.find(sig);
    if (rst == hanldes.end())
    {
        ::uv_signal_start(&signal, &SignalCtrl::onSignal, sig);
        hanldes.insert(pair<int, SignalHandle>(sig, handle)) ;
    }
    else
    {
        rst->second = handle;
    }
}

bool SignalCtrl::handle(int signum)
{
    auto rst = hanldes.find(signum);
    if (rst == hanldes.end())
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
