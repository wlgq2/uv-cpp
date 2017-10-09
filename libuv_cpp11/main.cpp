#include <iostream>
#include "EchoServer.h"
#include "uv/SignalCtrl.h"
#include "uv/Async.h"
#include "Clinet.h"

using namespace uv;

#define TEST_SERVER   1
#define TEST_CLIENT   1
#define TEST_ASYNC    1

int main(int argc,char** args)
{
    uv_loop_t* loop = uv_default_loop();
    //SignalCtrl signalCtrl(loop);
#if  TEST_SERVER
    EchoServer server(loop, 10003, "0.0.0.0");
    server.setTimeout(40);
    server.start();
#endif

#if  TEST_CLIENT
    Client client(loop);
    std::string ip ("192.168.1.132");
    client.connectToServer(ip,10002);
#endif

#if  TEST_ASYNC
	Async<int>* handle = new Async<int>(loop,std::bind(
    [](Async<int>* ptr, int* data)
    {
        std::cout << *data << std::endl;
        delete data;
        ptr->close();
        delete ptr;
    }, 
    std::placeholders::_1, std::placeholders::_2));
    int* data = new int;
    *data = 1024;
    handle->setData(data);
    handle->runInLoop();
#endif
    return ::uv_run(loop, UV_RUN_DEFAULT);
}
