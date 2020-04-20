/*
    Copyright © 2017-2019, orcaer@yeah.net  All rights reserved.

    Author: orcaer@yeah.net

    Last modified: 2019-10-20

    Description: https://github.com/wlgq2/uv-cpp
*/


#include <iostream>
#include <thread>
#include <memory>
#include <mutex>
#include <condition_variable>

#include "Client.h"


using namespace uv;

using ClientPtr = std::shared_ptr<Client>;

struct Clients
{
    std::vector<ClientPtr> clients ;
    std::mutex mutex ;
    std::condition_variable  condition ;
    bool inited;
};

void runClients(int count,SocketAddr& server,Clients& clients)
{
	EventLoop loop;
	{
        std::lock_guard<std::mutex> lock(clients.mutex);
        for (int i=0;i<count;i++)
        {
            auto client = std::make_shared<Client>(&loop);
            client->connectToServer(server);
            clients.clients.push_back(client);
        }
        clients.inited = true ;
	}
    clients.condition.notify_one();
	loop.run();
}


void runClientsCrossThread(Clients& clients)
{
    {
        std::unique_lock<std::mutex> lock(clients.mutex);
        clients.condition.wait(lock, [&clients] { return clients.inited; });
    }
	EventLoop loop;
	char data[] = "test";
	uv::Timer timer(&loop,1000,1000,
	[&clients,data](uv::Timer*)
	{
		for(auto ptr : clients.clients)
		{
			ptr->writeInLoop(data,sizeof(data),nullptr);
		}
	});
	timer.start();
	loop.run();
}

int main(int argc, char** args)
{
    SocketAddr addr("127.0.0.1",10005);
    struct Clients clients;
    clients.inited = false;
    //开1000客户端
    std::thread t1(std::bind(&runClients,1000,addr,std::ref(clients)));
    //跨线程发送消息
    std::thread t2(std::bind(&runClientsCrossThread,std::ref(clients)));
    t1.join();
    t2.join();
}
