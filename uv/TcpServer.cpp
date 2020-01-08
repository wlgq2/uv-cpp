/*
   Copyright © 2017-2019, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net

   Last modified: 2019-12-31

   Description: https://github.com/wlgq2/uv-cpp
*/


#include <functional>
#include <memory>
#include <string>

#include "include/TcpServer.h"
#include "include/LogWriter.h"

using namespace std;
using namespace uv;


TcpServer::TcpServer(EventLoop* loop, bool tcpNoDelay)
    :loop_(loop),
    tcpNoDelay_(tcpNoDelay),
    accetper_(nullptr),
    onMessageCallback_(nullptr),
    onNewConnectCallback_(nullptr),
    onConnectCloseCallback_(nullptr),
    timerWheel_(loop)
{

}

TcpServer:: ~TcpServer()
{

}

void TcpServer::setTimeout(unsigned int seconds)
{
    timerWheel_.setTimeout(seconds);
}

void uv::TcpServer::onAccept(EventLoop * loop, UVTcpPtr client)
{
    string key;
    SocketAddr::AddrToStr(client.get(), key, ipv_);

    uv::LogWriter::Instance()->info("new connect  " + key);
    shared_ptr<TcpConnection> connection(new TcpConnection(loop, key, client));
    if (connection)
    {
        connection->setMessageCallback(std::bind(&TcpServer::onMessage, this, placeholders::_1, placeholders::_2, placeholders::_3));
        connection->setConnectCloseCallback(std::bind(&TcpServer::closeConnection, this, placeholders::_1));
        addConnnection(key, connection);
        timerWheel_.insertNew(connection);
        if (onNewConnectCallback_)
            onNewConnectCallback_(connection);
    }
    else
    {
        uv::LogWriter::Instance()->error("create connection fail. :" + key);
    }
}

int TcpServer::bindAndListen(SocketAddr& addr)
{
    ipv_ = addr.Ipv();
    accetper_ = std::make_shared<TcpAccepter>(loop_, tcpNoDelay_);
    auto rst = accetper_->bind(addr);
    if (0 != rst)
    {
        return rst;
    }
    accetper_->setNewConnectinonCallback(std::bind(&TcpServer::onAccept, this, std::placeholders::_1, std::placeholders::_2));
    timerWheel_.start();
    return accetper_->listen();
}



void TcpServer::addConnnection(std::string& name,TcpConnectionPtr connection)
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
    auto connection = getConnnection(name);
    if (nullptr != connection)
    {
        connection->close([this](std::string& name)
        {
            auto connection = getConnnection(name);
            if (nullptr != connection)
            {
                if (onConnectCloseCallback_)
                {
                    onConnectCloseCallback_(connection);
                }
                connnections_.erase(name);
            }

        });
    }
}


void TcpServer::onMessage(TcpConnectionPtr connection,const char* buf,ssize_t size)
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
    if(nullptr != connection)
    {
        connection->write(buf,size, callback);
    }
    else if (callback)
    {
        WriteInfo info = { WriteInfo::Disconnected,const_cast<char*>(buf),size };
        callback(info);
    }
}

void TcpServer::write(string& name,const char* buf,unsigned int size,AfterWriteCallback callback)
{
    auto connection = getConnnection(name);
    write(connection, buf, size, callback);
}

void TcpServer::writeInLoop(shared_ptr<TcpConnection> connection,const char* buf,unsigned int size,AfterWriteCallback callback)
{
    if(nullptr != connection)
    {
        connection->writeInLoop(buf,size,callback);
    }
    else if (callback)
    {
        uv::LogWriter::Instance()->warn("try write a disconnect connection.");
        WriteInfo info = { WriteInfo::Disconnected,const_cast<char*>(buf),size };
        callback(info);
    }
}

void TcpServer::writeInLoop(string& name,const char* buf,unsigned int size,AfterWriteCallback callback)
{
    auto connection = getConnnection(name);
    writeInLoop(connection, buf, size, callback);
}

void TcpServer::setNewConnectCallback(OnConnectionStatusCallback callback)
{
    onNewConnectCallback_ = callback;
}

void  TcpServer::setConnectCloseCallback(OnConnectionStatusCallback callback)
{
    onConnectCloseCallback_ = callback;
}
