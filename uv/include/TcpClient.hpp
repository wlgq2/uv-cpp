/*
   Copyright © 2017-2019, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net

   Last modified: 2019-12-31

   Description: https://github.com/wlgq2/uv-cpp
*/

#ifndef   UV_TCP_CLIENT_HPP
#define   UV_TCP_CLIENT_HPP

#include  <functional>
#include  <memory>

#include  "TcpConnection.hpp"
#include  "SocketAddr.hpp"

namespace uv
{
using NewMessageCallback =  std::function<void(const char*,ssize_t)>  ;

class TcpClient
{
public:
    enum ConnectStatus
    {
        OnConnectSuccess,
        OnConnectFail,
        OnConnectClose
    };
    using ConnectStatusCallback = std::function<void(ConnectStatus)>;
public:
    TcpClient(EventLoop* loop,bool tcpNoDelay = true);
    virtual ~TcpClient();

    bool isTcpNoDelay();
    void setTcpNoDelay(bool isNoDelay);
    void connect(SocketAddr& addr);
    void close(std::function<void(uv::TcpClient*)> callback);

    int write(const char* buf, unsigned int size, AfterWriteCallback callback = nullptr);
    void writeInLoop(const char* buf, unsigned int size, AfterWriteCallback callback);

    void setConnectStatusCallback(ConnectStatusCallback callback);
    void setMessageCallback(NewMessageCallback callback);

    EventLoop* Loop();
    PacketBufferPtr getCurrentBuf();
protected:
    EventLoop* loop_;

    void onConnect(bool success);
    void onConnectClose(std::string& name);
    void onMessage(TcpConnectionPtr connection, const char* buf, ssize_t size);
    void afterConnectFail();
private:
    UVTcpPtr socket_;
    uv_connect_t* connect_;
    SocketAddr::IPV ipv;
    bool tcpNoDelay_;

    ConnectStatusCallback connectCallback_;
    NewMessageCallback onMessageCallback_;

    TcpConnectionPtr connection_;
    void update();
    void runConnectCallback(TcpClient::ConnectStatus success);
    void onClose(std::string& name);
};

using TcpClientPtr = std::shared_ptr<uv::TcpClient>;
}
#endif
