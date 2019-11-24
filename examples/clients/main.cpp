/*
    Copyright © 2017-2019, orcaer@yeah.net  All rights reserved.

    Author: orcaer@yeah.net

    Last modified: 2019-10-20

    Description: https://github.com/wlgq2/uv-cpp
*/


#include <iostream>
#include <thread>
#include <memory>

#include "Client.h"


using namespace uv;

using ClientPtr = std::shared_ptr<Client>;

void runClients(int count,SocketAddr& server,std::vector<ClientPtr>& clients)
{
	EventLoop loop;
	for (int i=0;i<count;i++)
	{
		auto client = std::make_shared<Client>(&loop);
		client->connectToServer(server);
		clients.push_back(client);
	}
	loop.run();
}


void runClientsCrossThread(std::vector<ClientPtr>& clients)
{
	EventLoop loop;
	char data[] = "test";
	uv::Timer timer(&loop,1000,1000,
	[&clients,data](uv::Timer*)
	{
		for(auto ptr : clients)
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
    std::vector<ClientPtr> clients;
    //开1000客户端
    std::thread t1(std::bind(&runClients,1000,addr,clients));
    //跨线程发送消息
    std::thread t2(std::bind(&runClientsCrossThread,clients));
    t1.join();
    t2.join();
}
