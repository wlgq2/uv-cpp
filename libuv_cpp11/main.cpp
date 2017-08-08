#include <iostream>
#include "EchoServer.h"
#include "uv/SignalCtrl.h"
#include "Clinet.h"

using namespace uv;

int main(int argc,char** args)
{

    uv_loop_t* loop = uv_default_loop();
    SignalCtrl signalCtrl(loop);

    EchoServer server(loop, 10005, "0.0.0.0");
    server.setTimeout(10);
    server.start();

    Client client(loop);
    client.connect("192.168.141.73",10010);
    return ::uv_run(loop, UV_RUN_DEFAULT);
}
