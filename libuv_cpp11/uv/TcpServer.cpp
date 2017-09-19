/*
   Copyright 2017, object_he@yeah.net  All rights reserved.

   Author: object_he@yeah.net

   Last modified: 2017-8-14

   Description:
*/

#include "TcpServer.h"
#include <iostream>
#include <functional>
#include <memory>



using namespace std;
using namespace uv;


TcpServer::TcpServer(uv_loop_t* loop,int port ,const char* ip )
    :loop(loop),
    accetper(new TcpAccepter(loop,ip,port)),
    onMessageCallback(nullptr),
    onNewConnectCallback(nullptr),
    timerWheel(loop)
{
    accetper->setNewConnectinonCallback( [this] (uv_loop_t* loop,uv_tcp_t* client)
    {
        struct sockaddr_in addr;
        int len = sizeof(struct sockaddr_in);
        ::uv_tcp_getpeername(client,(struct sockaddr *)&addr,&len);
        string key(inet_ntoa(addr.sin_addr));
        key+=":"+std::to_string(htons(addr.sin_port));
        cout<<"new connect  "<<key<<endl;

        shared_ptr<TcpConnection> connection(new TcpConnection(loop,key,client));
        if(connection)
        {
            connection->setMessageCallback(std::bind(&TcpServer::onMessage,this,placeholders::_1,placeholders::_2,placeholders::_3));
            connection->setConnectCloseCallback(std::bind(&TcpServer::closeConnection,this,placeholders::_1));
            addConnnection(key,connection);
            timerWheel.insertNew(connection);
            if(onNewConnectCallback)
                onNewConnectCallback(connection);
        }
        else
        {
            cout<<"can not create connection. :"<<inet_ntoa(addr.sin_addr)<<":"<<htons(addr.sin_port)<<endl;
        }

    });
}



TcpServer:: ~TcpServer()
{

}


void TcpServer::setTimeout(unsigned int timeout)
{
    timerWheel.setTimeout(timeout);
}

void TcpServer::start()
{
    timerWheel.start();
    accetper->listen();
}



void TcpServer::addConnnection(std::string& name,std::shared_ptr<TcpConnection> connection)
{
    connnections.insert(pair<string,shared_ptr<TcpConnection>>(name,connection));
}

void TcpServer::removeConnnection(string& name)
{
    connnections.erase(name);
}

shared_ptr<TcpConnection> TcpServer::getConnnection(string& name)
{
    auto rst = connnections.find(name);
    if(rst == connnections.end())
    {
        return nullptr;
    }
    return rst->second;
}

void TcpServer::closeConnection(string& name)
{
    if(nullptr != getConnnection(name))
        connnections.erase(name);
}


void TcpServer::onMessage(std::shared_ptr<TcpConnection> connection,const char* buf,ssize_t size)
{
    if(onMessageCallback)
        onMessageCallback(connection,buf,size);
    timerWheel.insert(connection);
}


void TcpServer::setMessageCallback(OnMessageCallback callback)
{
    onMessageCallback = callback;
}


void TcpServer::write(shared_ptr<TcpConnection> connection,const char* buf,unsigned int size)
{
    if(connection)
    {
        connection->write(buf,size,nullptr);
    }
}

void TcpServer::write(string& name,const char* buf,unsigned int size)
{
    auto connection = getConnnection(name);
    if(connection)
    {
        connection->write(buf,size,nullptr);
    }
}

void TcpServer::writeInLoop(shared_ptr<TcpConnection> connection,const char* buf,unsigned int size,AfterWriteCallback callback)
{
    if(connection)
    {
        connection->writeInLoop(buf,size,callback);
    }

}

void TcpServer::writeInLoop(string& name,const char* buf,unsigned int size,AfterWriteCallback callback)
{
    auto connection = getConnnection(name);
    if(connection)
    {
        connection->writeInLoop(buf,size,callback);
    }
}

void TcpServer::setNewConnectCallback(OnNewConnectCallback callback)
{
    onNewConnectCallback = callback;
}
