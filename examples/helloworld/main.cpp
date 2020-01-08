#include <iostream>
#include <uv/include/uv11.h>


int main(int argc, char** args)
{
    //event's loop
    //uv::EventLoop* loop = new uv::EventLoop();
	//or
    uv::EventLoop* loop = uv::EventLoop::DefaultLoop();
    
    uv::SocketAddr serverAddr("127.0.0.1", 10000, uv::SocketAddr::Ipv4);
    //Tcp Server
    uv::TcpServer server(loop);
    server.setMessageCallback(
        [](uv::TcpConnectionPtr conn, const char* data , ssize_t size)
    {
        std::cout << std::string(data, size) << std::endl;
        std::string str("hex :");
        uv::LogWriter::ToHex(str, data, (unsigned int)size);
        std::cout << str << std::endl;
        conn->write(data, size,nullptr);
    });
    server.bindAndListen(serverAddr);


    //Tcp Client
    uv::TcpClient client(loop);
    client.setConnectStatusCallback(
        [&client](uv::TcpClient::ConnectStatus status)
    {
        if (status == uv::TcpClient::ConnectStatus::OnConnectSuccess)
        {
            char data[] = "hello world!";
            client.write(data, sizeof(data));
        }
        else
        {
            std::cout << "Error : connect to server fail" << std::endl;
        }
    });
    client.connect(serverAddr);

    loop->run();
}
