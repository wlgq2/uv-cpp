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
