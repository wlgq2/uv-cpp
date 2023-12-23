/*
   Copyright © 2017-2019, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net

   Last modified: 2019-12-31

   Description: https://github.com/wlgq2/uv-cpp
*/

#ifndef UV_TCP_CONNECTION_HPP
#define UV_TCP_CONNECTION_HPP

#include <memory>


#include <chrono>
#include <functional>
#include <atomic>
#include <string>

#include "EventLoop.hpp"
#include "ListBuffer.hpp"
#include "CycleBuffer.hpp"
#include "SocketAddr.hpp"

namespace uv
{

struct WriteInfo
{
	static const int Disconnected = -1;
	int status;
	char* buf;
	unsigned long size;
};


class TcpConnection ;
class TcpServer;
class ConnectionWrapper;

using TcpConnectionPtr = std::shared_ptr<TcpConnection>;
using AfterWriteCallback =  std::function<void (WriteInfo& )> ;
using OnMessageCallback =  std::function<void (TcpConnectionPtr,const char*,ssize_t)>  ;
using OnCloseCallback =  std::function<void (std::string& )>  ;
using CloseCompleteCallback =  std::function<void (std::string&)>  ;


class TcpConnection : public std::enable_shared_from_this<TcpConnection>
{
public :
    TcpConnection(EventLoop* loop,std::string& name,UVTcpPtr client,bool isConnected = true);
    virtual ~TcpConnection();
    
    void onSocketClose();
    void close(std::function<void(std::string&)> callback);

    int write(const char* buf,ssize_t size,AfterWriteCallback callback);
    void writeInLoop(const char* buf,ssize_t size,AfterWriteCallback callback);

    void setWrapper(std::shared_ptr<ConnectionWrapper> wrapper);
    std::shared_ptr<ConnectionWrapper> getWrapper();

    void setMessageCallback(OnMessageCallback callback);
    void setConnectCloseCallback(OnCloseCallback callback);
    
    void setConnectStatus(bool status);
    bool isConnected();
    
    const std::string& Name();

    PacketBufferPtr getPacketBuffer();
private:
    void onMessage(const char* buf, ssize_t size);
    void CloseComplete();
    char* resizeData(size_t size);
    static void  onMesageReceive(uv_stream_t* client, ssize_t nread, const uv_buf_t* buf);
    
private :
    std::string name_;
    bool connected_;
    EventLoop* loop_;
    UVTcpPtr handle_;
    std::string data_;
    PacketBufferPtr buffer_;
    std::weak_ptr<ConnectionWrapper> wrapper_;

    OnMessageCallback onMessageCallback_;
    OnCloseCallback onConnectCloseCallback_;
    CloseCompleteCallback closeCompleteCallback_;
};

class  ConnectionWrapper : public std::enable_shared_from_this<ConnectionWrapper>
{
public:
    ConnectionWrapper(TcpConnectionPtr connection)
        :connection_(connection)
    {
    }

    ~ConnectionWrapper()
    {
        TcpConnectionPtr connection = connection_.lock();
        if (connection)
        {
            connection->onSocketClose();
        }
    }

private:
    std::weak_ptr<TcpConnection> connection_;
};
using ConnectionWrapperPtr = std::shared_ptr<ConnectionWrapper>;
}
#endif
