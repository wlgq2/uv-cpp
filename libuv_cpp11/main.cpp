#include <iostream>
#include "EchoServer.h"
#include "uv/SignalCtrl.h"
#include "uv/Async.h"
#include "Clinet.h"

using namespace uv;

#define      TEST_SIGNAL      1
#define      TEST_SERVER      1
#define      TEST_CLIENT      1
#define      TEST_ASYNC       1
#define      TEST_TIMER       1


int main(int argc,char** args)
{
    uv_loop_t* loop = uv_default_loop();

//接管信号
#if    TEST_SIGNAL
    SignalCtrl signalCtrl(loop);
#endif


//server对象
#if  TEST_SERVER
    EchoServer server(loop, 10003, "0.0.0.0");
    server.setTimeout(40);
    server.start();
#endif


//client对象
#if  TEST_CLIENT
    Client client(loop);
    std::string ip ("192.168.1.132");
    client.connectToServer(ip,10002);
#endif


//loop线程中异步执行函数。
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


//定时器测试
#if  TEST_TIMER
    Timer<void*> timer(loop,1000,1000, std::bind(
        [](void*)
    {
        std::cout << "timer callback with null arg"<< std::endl;
    },
    std::placeholders::_1), nullptr);
    timer.start();
#endif

    return ::uv_run(loop, UV_RUN_DEFAULT);
}
