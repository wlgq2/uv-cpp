#include <iostream>


#include "EchoServer.h"
#include "Clinet.h"


using namespace uv;



int main(int argc, char** args)
{
    //定义事件分发器类
    EventLoop* loop = EventLoop::DefaultLoop();

    uv::GlobalConfig::BufferModeStatus = uv::GlobalConfig::CycleBuffer;
    SocketAddr addr1("0.0.0.0", 10002, SocketAddr::Ipv4);


    EchoServer server(loop);
    server.setTimeout(60);
    server.bindAndListen(addr1);

    SocketAddr addr2("127.0.0.1", 10002);

    Client client(loop);
    client.connectToServer(addr2);


    Timer timer(loop, 1000, 1000,
        [&server](Timer*)
    {
        std::cout << "cnt:"<<server.Cnt()<< std::endl;
        server.clearCnt();
    });

    timer.start();

    loop->run();
    delete loop;
}
