#include <iostream>


#include "EchoServer.h"
#include "Clinet.h"
#include "LogDemo.h"

using namespace uv;

#define      TEST_SIGNAL      0
#define      TEST_SERVER      1
#define      TEST_CLIENT      1
#define      TEST_ASYNC       0
#define      TEST_TIMER       0
#define      TEST_LOG         1

#define       TEST_IPV6        0

int main(int argc, char** args)
{
    //定义事件分发器类
    EventLoop* loop = new EventLoop(EventLoop::DefaultLoop);

    //接管信号
#if    TEST_SIGNAL
    SignalCtrl signalCtrl(loop);
#endif


    //server对象
#if   TEST_SERVER
#if    TEST_IPV6 
    SocketAddr addr1("0:0:0:0:0:0:0:0", 10002, SocketAddr::Ipv6);
#else
    SocketAddr addr1("0.0.0.0", 10002, SocketAddr::Ipv4);
#endif

    EchoServer server(loop, addr1);
    server.setTimeout(40);
    server.start();
#endif


    //client对象
#if  TEST_CLIENT
#if    TEST_IPV6
    SocketAddr addr2("0:0:0:0:0:0:0:1", 10002, SocketAddr::Ipv6);
#else
    SocketAddr addr2("127.0.0.1", 10002, SocketAddr::Ipv4);
#endif
    Client client(loop);
    client.connectToServer(addr2);
#endif


    //loop线程中异步执行函数
#if  TEST_ASYNC
    Async<int>* handle = new Async<int>(loop, std::bind(
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
    Timer<void*> timer(loop, 1000, 1000, std::bind(
        [](void*)
    {
        std::cout << "timer callback with null arg" << std::endl;
    },
        std::placeholders::_1), nullptr);
    timer.start();
#endif

#if  TEST_LOG
    auto log = uv::Log::Instance();
    log->registerInterface(new LogDemo);

    log->debug("debug message");
    log->warn("warn message");
    log->error("error message");
    log->info("info message");
#endif
    loop->run();
}