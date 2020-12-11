/*
   Copyright © 2017-2020, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net

   Last modified: 2020-4-20

   Description: https://github.com/wlgq2/uv-cpp
*/

#include <iostream>
#include <uv/include/uv11.hpp>

void startClients(uv::EventLoop* loop,uv::SocketAddr& addr,std::vector<uv::TcpClientPtr>& clients,uint64_t cnt)
{
    for(uint64_t i=0;i<cnt;i++)
    {
        uv::TcpClientPtr client = std::make_shared<uv::TcpClient>(loop);
        client->setConnectStatusCallback(
            [client](uv::TcpClient::ConnectStatus status)
        {
            if (status == uv::TcpClient::ConnectStatus::OnConnectSuccess)
            {
                char data[4096] = "hello world!";
                client->write(data, sizeof(data));
            }
            else
            {
                std::cout << "Error : connect to server fail" << std::endl;
            }
        });
        client->setMessageCallback([client](const char* data,ssize_t size)
        {
            client->write(data,(unsigned)size,nullptr);
        });

        client->connect(addr);
        clients.push_back(client);
    }
}

int main(int argc, char** args)
{
    uv::EventLoop* loop = uv::EventLoop::DefaultLoop();

    uv::SocketAddr serverAddr("127.0.0.1", 10005, uv::SocketAddr::Ipv4);
    std::vector<uv::TcpClientPtr> clients;
    startClients(loop,serverAddr,clients,1);

    loop->run();
}
