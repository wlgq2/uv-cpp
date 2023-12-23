#include <iostream>
#include <uv/include/uv11.hpp>

using namespace uv;
using namespace std;

void server_test(EventLoop* loop, TcpServer& server,bool& status, vector<TcpClientPtr>& clients)
{
    status = !status;
    if (status) //开始监听server
    {
        uv::SocketAddr addr("0.0.0.0", 10001);
        server.bindAndListen(addr);
        //客户端连接server
        for (auto& client : clients)
        {
            uv::SocketAddr serverAddr("127.0.0.1", 10001);
            client->connect(serverAddr);
        }
    }
    else //关闭server
    {
        server.close([]() 
        {
            cout << "on server closed" << std::endl << std::endl;
        });
    }
}
int main(int argc, char** args)
{
    EventLoop loop;
    bool status = false;
    //创建server。
    TcpServer server(&loop);
    //创建5个客户端。
    vector<TcpClientPtr> clients(5);
    for (auto& client : clients)
        client = make_shared<TcpClient>(&loop);
    //重复开始/停止server。
    Timer timer(&loop, 2000, 2000, std::bind(&server_test, &loop, std::ref(server), std::ref(status),std::ref(clients)));
    timer.start();
    loop.run();
}
