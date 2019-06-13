#include <iostream>
#include <uv/uv11.h>


int main(int argc, char** args)
{
    //event's loop
    uv::EventLoop* loop = uv::EventLoop::DefalutLoop();

    //Tcp Server
    uv::SocketAddr serverAddr("0.0.0.0", 10002, uv::SocketAddr::Ipv4);
    uv::TcpServer server(loop, serverAddr);
    server.setMessageCallback(
        [](std::shared_ptr<uv::TcpConnection> conn, const char* data , ssize_t size)
    {
        std::cout << std::string(data, size) << std::endl;
        conn->write(data, size,nullptr);
    });
    server.start();

    //Tcp Client
    uv::TcpClient client(loop);
    client.setConnectCallback(
        [&client](bool isSuccess)
    {
        if (isSuccess)
        {
            char data[] = "hello world!";
            client.write(data, sizeof(data));
        }
    });
    client.connect(serverAddr);
       
    loop->run();
}
