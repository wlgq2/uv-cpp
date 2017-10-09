/*
   Copyright 2017, object_he@yeah.net  All rights reserved.

   Author: object_he@yeah.net

   Last modified: 2017-9-19

   Description:
*/

#include <iostream>
#include "uv/TcpClient.h"
#include <string>

using namespace uv;
using namespace std;


TcpClient::TcpClient(uv_loop_t* loop)
    :loop(loop),
    socket(new uv_tcp_t()),
    connect_(new uv_connect_t()),
    connectCallback(nullptr),
    onMessageCallback(nullptr),
    onConnectCloseCallback(nullptr),
    tcpConnection(nullptr)
{
    ::uv_tcp_init(loop, socket);
    socket->data = (void*)this;
}

TcpClient::~TcpClient()
{
    delete connect_;
}


void TcpClient::connect(const char* ip, unsigned short port)
{
    ::uv_ip4_addr(ip, port, &dest);
    ::uv_tcp_connect(connect_, socket, (struct sockaddr*)&dest, [](uv_connect_t* req, int status)
    {
        auto handle = (TcpClient*)(((uv_tcp_t *)(req->handle))->data);
        if (0 != status)
        {
            cout << "connect fail." << endl;
            handle->onConnect(false);
            return;
        }

        handle->onConnect(true);

    });
}

void TcpClient::onConnect(bool successed)
{
    if(successed)
    {
        struct sockaddr_in addr;
        int len = sizeof(struct sockaddr_in);
        ::uv_tcp_getpeername(socket,(struct sockaddr *)&addr,&len);
        string name(inet_ntoa(addr.sin_addr));
        name+=":"+std::to_string(htons(addr.sin_port));

        shared_ptr<TcpConnection> connection(new TcpConnection(loop,name,socket));
        tcpConnection = connection;
        tcpConnection->setMessageCallback(std::bind(&TcpClient::onMessage,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3));
        tcpConnection->setConnectCloseCallback(std::bind(&TcpClient::onConnectClose,this,std::placeholders::_1));
    }
    if(connectCallback)
        connectCallback(successed);
}
void TcpClient::onConnectClose(string& name)
{
    updata();
    if(onConnectCloseCallback)
        onConnectCloseCallback();
}
void TcpClient::onMessage(shared_ptr<TcpConnection> connection,const char* buf,ssize_t size)
{
    if(onMessageCallback)
        onMessageCallback(buf,size);
}

void TcpClient::updata()
{
    tcpConnection = nullptr;
    socket = new uv_tcp_t();
    ::uv_tcp_init(loop, socket);
    socket->data = (void*)this;
}
