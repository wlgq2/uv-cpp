#include <iostream>
#include "EchoServer.h"
#include "SignalCtrl.h"

using namespace uv;

int main(int argc,char** args)
{

    uv_loop_t* loop = uv_default_loop();
    SignalCtrl signalCtrl(loop);

    EchoServer server(loop, 10005, "0.0.0.0");
    server.setTimeout(10);
    server.start();

    return ::uv_run(loop, UV_RUN_DEFAULT);
}
