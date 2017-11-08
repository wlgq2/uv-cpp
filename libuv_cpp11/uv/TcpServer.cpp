/*
   Copyright 2017, object_he@yeah.net  All rights reserved.

   Author: object_he@yeah.net

   Last modified: 2017-11-8

   Description:
*/

#include "TcpServer.h"
#include <iostream>
#include <functional>
#include <memory>
#include <string>


using namespace std;
using namespace uv;


TcpServer::TcpServer(EventLoop* loop, SocketAddr& addr)
    :loop_(loop),
    ipv_(addr.Ipv()),
    accetper_(new TcpAccepter(loop, addr)),
    onMessageCallback_(nullptr),
    onNewConnectCallback_(nullptr),
    timerWheel_(loop)
{
    accetper_->setNewConnectinonCallback( [this] (EventLoop* loop,uv_tcp_t* client)
    {
        string key;
        SocketAddr::AddrToStr(client,key, ipv_);

        cout<<"new connect  "<<key<<endl;

        shared_ptr<TcpConnection> connection(new TcpConnection(loop,key,client));
        if(connection)
        {
            connection->setMessageCallback(std::bind(&TcpServer::onMessage,this,placeholders::_1,placeholders::_2,placeholders::_3));
            connection->setConnectCloseCallback(std::bind(&TcpServer::closeConnection,this,placeholders::_1));
            addConnnection(key,connection);
            timerWheel_.insertNew(connection);
            if(onNewConnectCallback_)
                onNewConnectCallback_(connection);
        }
        else
        {
            cout<<"can not create connection. :"<< key <<endl;
        }

    });
}



TcpServer:: ~TcpServer()
{

}


void TcpServer::setTimeout(unsigned int timeout)
{
    timerWheel_.setTimeout(timeout);
}

void TcpServer::start()
{
    timerWheel_.start();
    accetper_->listen();
}



void TcpServer::addConnnection(std::string& name,std::shared_ptr<TcpConnection> connection)
{
    connnections_.insert(pair<string,shared_ptr<TcpConnection>>(std::move(name),connection));
}

void TcpServer::removeConnnection(string& name)
{
    connnections_.erase(name);
}

shared_ptr<TcpConnection> TcpServer::getConnnection(string& name)
{
    auto rst = connnections_.find(name);
    if(rst == connnections_.end())
    {
        return nullptr;
    }
    return rst->second;
}

void TcpServer::closeConnection(string& name)
{
    if(nullptr != getConnnection(name))
        connnections_.erase(name);
}


void TcpServer::onMessage(std::shared_ptr<TcpConnection> connection,const char* buf,ssize_t size)
{
    if(onMessageCallback_)
        onMessageCallback_(connection,buf,size);
    timerWheel_.insert(connection);
}


void TcpServer::setMessageCallback(OnMessageCallback callback)
{
    onMessageCallback_ = callback;
}


void TcpServer::write(shared_ptr<TcpConnection> connection,const char* buf,unsigned int size, AfterWriteCallback callback)
{
    if(connection)
    {
        connection->write(buf,size, callback);
    }
}

void TcpServer::write(string& name,const char* buf,unsigned int size,AfterWriteCallback callback)
{
    auto connection = getConnnection(name);
    if(connection)
    {
        connection->write(buf,size, callback);
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
    onNewConnectCallback_ = callback;
}
