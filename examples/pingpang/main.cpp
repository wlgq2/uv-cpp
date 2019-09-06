#include <iostream>


#include "EchoServer.h"
#include "Clinet.h"


using namespace uv;



int main(int argc, char** args)
{
    //定义事件分发器类
    EventLoop* loop = EventLoop::DefalutLoop();

    SocketAddr addr1("0.0.0.0", 10002, SocketAddr::Ipv4);


    EchoServer server(loop, addr1);
    server.setTimeout(40);
    server.start();

    SocketAddr addr2("127.0.0.1", 10002);

    Client client(loop);
    client.connectToServer(addr2);


    Timer<EchoServer*> timer(loop, 1000, 1000,
    [](Timer<EchoServer*>*,EchoServer* server)
    {
        std::cout << "cnt:"<<server->Cnt()<< std::endl;
        server->clearCnt();
    },&server );

    timer.start();

    loop->run();
    delete loop;
}
