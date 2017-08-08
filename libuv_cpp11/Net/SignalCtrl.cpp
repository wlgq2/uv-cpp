#include <iostream>
#include "SignalCtrl.h"

using namespace uv;
using namespace std;

SignalCtrl::SignalCtrl(uv_loop_t* loop)
{
    ::uv_signal_init(loop, &signal);
    ::uv_signal_start(&signal,&SignalCtrl::onSignal, SIGPIPE);
}

void SignalCtrl::onSignal(uv_signal_t* handle, int signum)
{
    switch (signum)
    {

        case SIGPIPE:
        {
            cout<<"signal: broken pipe"<<endl;
        }
        default:
            cout<<"signal:"<<signum<<endl;
            break;
    }

}
