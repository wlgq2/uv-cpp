/*
    Copyright © 2017-2019, orcaer@yeah.net  All rights reserved.

    Author: orcaer@yeah.net

    Last modified: 2019-10-20

    Description: https://github.com/wlgq2/uv-cpp
*/


#include <iostream>


#include "EchoServer.h"
#include "Clinet.h"
#include <chrono>

using namespace uv;

#define      TEST_SIGNAL      1
#define      TEST_SERVER      1
#define      TEST_CLIENT      1
#define      TEST_ASYNC       1
#define      TEST_TIMER       1
#define      TEST_LOG         1
#define      TEST_UDP         1

#define       TEST_IPV6       0

int main(int argc, char** args)
{
    //定义事件分发器类
    EventLoop* loop = new EventLoop();
    //or
    //EventLoop* loop = EventLoop::DefaultLoop();

#if    TEST_SIGNAL
    //接管SIGPIPE信号。
    Signal signal(loop,13,[](int sig)
    {
        //SIGPIPE
    });

#endif


    //server对象
#if   TEST_SERVER
#if    TEST_IPV6
    SocketAddr addr1("0:0:0:0:0:0:0:0", 10002, SocketAddr::Ipv6);
#else
    SocketAddr addr1("0.0.0.0", 10002, SocketAddr::Ipv4);
#endif

    EchoServer server(loop);
    //心跳超时
    server.setTimeout(40);
    server.bindAndListen(addr1);
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

#if  1

    //跨线程发送数据
    std::thread thread([&client]()
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        char* data = new char[4] {'t','e','s','t'};
       
        //线程安全;
        client.writeInLoop(data,sizeof(data),
            [](uv::WriteInfo& info)
        {
            //数据需要在发生完成回调中释放
            //write message error.
            if (0 != info.status)
            {
                //打印错误信息
                std::cout << "Write error ：" << EventLoop::GetErrorMessage(info.status) << std::endl;
            }
            delete[] info.buf;
        });
    });
#endif

#endif


    //loop线程中异步执行函数，用于跨线程操作。
    //相对于原生libuv async接口，修复了调用多次可能只运行一次的问题。
#if  TEST_ASYNC
    loop->runInThisLoop(
        []()
    {
        std::cout << "run function in loop thread one." << std::endl;
    });

    loop->runInThisLoop(
        []()
    {
        std::cout << "run function in loop thread two." << std::endl;
    });
#endif


    //定时器测试
#if  TEST_TIMER
    Timer timer(loop, 1000, 1000,
        [](Timer*)
    {
        std::cout << "timer callback test..." << std::endl;
    });
    timer.start();

    //定时器只运行一次及释放,可用于tcp重连,单次消息超时等。
    Timer* pTimer  =new Timer(loop, 1000, 0,
        [](Timer* handle)
    {
        std::cout << "timer callback run onice."<< std::endl;
        handle->close([](Timer* ptr)
        {
            std::cout << "release timer ptr."<< std::endl;
            //释放定时器对象。
            delete ptr;
        });
    });
    pTimer->start();
#endif

    //log接口绑定
#if  TEST_LOG
    auto log = uv::LogWriter::Instance();
    log->registerInterface(
        [](int level, const std::string& info)
    {
        std::cout <<uv::LogWriter::Instance()->getLevelName( level) << " :" << info << std::endl;
    });
    log->setLevel(uv::LogWriter::Debug);
    log->debug("debug message");
    log->info("info message");
    log->warn("warn message");
    log->error("error message");
    log->fatal("fatal message");
#endif


#if  TEST_UDP
    SocketAddr addr3("127.0.0.1", 10003);
    uv::Udp udpReceive(loop);
    udpReceive.setMessageCallback(
        [&udpReceive](SocketAddr& from,const char* data,unsigned size)
    {
        std::string msg(data, size);
        std::cout << "udp receive message from "<< from.toStr()<<" :" << msg << std::endl;
        udpReceive.send(from, data, size);
    });
    udpReceive.bindAndRead(addr3);

    SocketAddr addr4("127.0.0.1", 10004);
    uv::Udp udpSend(loop );
    udpSend.setMessageCallback(
        [](SocketAddr& from, const char* data, unsigned size)
    {
        std::string msg(data, size);
        std::cout << "udp call message :" << msg << std::endl;;
    });
    udpSend.bindAndRead(addr4);
    char udpmsg[] = "udp test...";
    udpSend.send(addr3, udpmsg, sizeof(udpmsg));
#endif

    loop->run();
    delete loop;
}