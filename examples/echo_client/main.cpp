#include <iostream>
#include <uv/include/uv11.h>


int main(int argc, char** args)
{
    uv::EventLoop* loop = uv::EventLoop::DefaultLoop();

    uv::SocketAddr serverAddr("127.0.0.1", 10005, uv::SocketAddr::Ipv4);

    //Tcp Client
    uv::TcpClient client(loop);
    client.setConnectStatusCallback(
        [&client](uv::TcpClient::ConnectStatus status)
    {
        if (status == uv::TcpClient::ConnectStatus::OnConnectSuccess)
        {
            char data[4096] = "hello world!";
            client.write(data, sizeof(data));
        }
        else
        {
            std::cout << "Error : connect to server fail" << std::endl;
        }
    });
    client.setMessageCallback([&client](const char* data,ssize_t size)
    {
        client.write(data,size,nullptr);
    });

    client.connect(serverAddr);


    loop->run();
}
