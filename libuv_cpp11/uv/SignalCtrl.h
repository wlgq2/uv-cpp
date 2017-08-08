/*
   Copyright 2017, object_he@yeah.net  All rights reserved.

   Author: object_he@yeah.net 
    
   Last modified: 2017-8-8
    
   Description: 
*/

#ifndef SIGNAL_CTRL_H
#define SIGNAL_CTRL_H

#include <uv.h>


namespace uv
{

class SignalCtrl
{
public:
    SignalCtrl(uv_loop_t* loop);
private:
    uv_signal_t signal;

    static void onSignal(uv_signal_t* handle, int signum);
};

}
#endif
