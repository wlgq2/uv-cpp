/*
   Copyright 2017, object_he@yeah.net  All rights reserved.

   Author: object_he@yeah.net 
    
   Last modified: 2017-8-8
    
   Description: 
*/

#include "TcpAccepter.h"
#include <iostream>


using namespace std;
using namespace uv;

TcpAccepter::TcpAccepter(uv_loop_t* loop,const char* ip,int port)
    :loop(nullptr),
    newConnectionCallback(nullptr)
{
    struct sockaddr_in addr;
    this->loop =loop;
    ::uv_ip4_addr(ip, port,&addr);
    ::uv_tcp_init(loop, &server);
    ::uv_tcp_bind(&server, (const sockaddr*)&addr,0);
    server.data = (void* )this;
}



TcpAccepter:: ~TcpAccepter()
{

}

uv_loop_t* TcpAccepter::getLoop()
{
    return loop;
}

void TcpAccepter::onNewConnect(uv_tcp_t* client)
{
    if(nullptr !=newConnectionCallback)
    {
        newConnectionCallback(loop,client);
    }
}

void TcpAccepter::listen()
{
    ::uv_listen((uv_stream_t*) &server, 128,
    [](uv_stream_t *server, int status)
    {
        if (status < 0)
        {
            cout<< "New connection error"<<uv_strerror(status)<<endl;
            return;
        }
        TcpAccepter* accept = static_cast<TcpAccepter*>(server->data);
        uv_tcp_t* client =new uv_tcp_t();
        uv_tcp_init(accept->getLoop(), client);

        if ( 0 == ::uv_accept(server, (uv_stream_t*) client))
        {
            accept->onNewConnect(client);
        }
        else
        {
            ::uv_close((uv_handle_t*) client, NULL);
            delete client;
        }
    });
    listened = true;
}


bool TcpAccepter::isListen()
{
    return listened;
}

void TcpAccepter::setNewConnectinonCallback(NewConnectionCallback callback)
{
    newConnectionCallback = callback;
}
