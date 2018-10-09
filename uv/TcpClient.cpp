/*
   Copyright 2017, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net

   Last modified: 2018-10-9

   Description: https://github.com/wlgq2/libuv_cpp11
*/

#include <string>

#include "TcpClient.h"
#include "LogInterface.h"

using namespace uv;
using namespace std;


TcpClient::TcpClient(EventLoop* loop, bool tcpNoDelay)
    :loop_(loop),
    socket_(new uv_tcp_t()),
    connect_(new uv_connect_t()),
    ipv(SocketAddr::Ipv4),
    tcpNoDelay_(tcpNoDelay),
    connectCallback_(nullptr),
    onMessageCallback_(nullptr),
    onConnectCloseCallback_(nullptr),
    connection_(nullptr)
{
    update();
}

TcpClient::~TcpClient()
{
    delete connect_;
}

bool uv::TcpClient::isTcpNoDelay()
{
    return tcpNoDelay_;
}

void uv::TcpClient::setTcpNoDelay(bool isNoDelay)
{
    tcpNoDelay_ = isNoDelay;
}


void TcpClient::connect(SocketAddr& addr)
{
    ipv = addr.Ipv();
    ::uv_tcp_connect(connect_, socket_, addr.Addr(), [](uv_connect_t* req, int status)
    {
        auto handle = static_cast<TcpClient*>(((uv_tcp_t *)(req->handle))->data);
        if (0 != status)
        {
            uv::Log::Instance()->error( "connect fail.");
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
        string name;
        SocketAddr::AddrToStr(socket_,name,ipv);

        connection_ = make_shared<TcpConnection>(loop_, name, socket_);
        connection_->setMessageCallback(std::bind(&TcpClient::onMessage,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3));
        connection_->setConnectCloseCallback(std::bind(&TcpClient::onConnectClose,this,std::placeholders::_1));
        runConnectCallback(successed);
    }
    else
    {
        if (::uv_is_active((uv_handle_t*)socket_))
        {
            ::uv_read_stop((uv_stream_t*)socket_);
        }
        if (::uv_is_closing((uv_handle_t*)socket_) == 0)
        {
            ::uv_close((uv_handle_t*)socket_,
                [](uv_handle_t* handle)
            {
                auto client = static_cast<TcpClient*>(handle->data);
                client->afterConnectFail();
                delete handle;
            });
        }
    }
}
void TcpClient::onConnectClose(string& name)
{
    if (connection_)
    {
        connection_->close([this](std::string& name)
        {
            //connection_ = nullptr;
            //old socket_ pointer will release when reconnect.
            socket_ = new uv_tcp_t();
            update();
            uv::Log::Instance()->info("Close tcp client connection complete.");
            if (onConnectCloseCallback_)
                onConnectCloseCallback_();
        });
    }

}
void TcpClient::onMessage(shared_ptr<TcpConnection> connection,const char* buf,ssize_t size)
{
    if(onMessageCallback_)
        onMessageCallback_(buf,size);
}

void uv::TcpClient::close(std::function<void(std::string&)> callback)
{
    if (connection_)
    {
        connection_->close(callback);
    }
    else if(callback)
    {
        std::string str("");
        callback(str);
    }
}

void uv::TcpClient::afterConnectFail()
{
    socket_ = new uv_tcp_t();
    update();
    runConnectCallback(false);
}

void uv::TcpClient::write(const char* buf, unsigned int size, AfterWriteCallback callback)
{
    if (connection_)
    {
        connection_->write(buf, size, callback);
    }
    else if(callback)
    {
        uv::Log::Instance()->warn("try write a disconnect connection.");
        WriteInfo info = { WriteInfo::Disconnected,const_cast<char*>(buf),size };
        callback(info);
    }

}

void uv::TcpClient::writeInLoop(const char * buf, unsigned int size, AfterWriteCallback callback)
{
    if (connection_)
    {
        connection_->writeInLoop(buf, size, callback);
    }
    else if(callback)
    {
        uv::Log::Instance()->warn("try write a disconnect connection.");
        WriteInfo info = { WriteInfo::Disconnected,const_cast<char*>(buf),size };
        callback(info);
    }
}

void uv::TcpClient::setConnectCallback(ConnectCallback callback)
{
    connectCallback_ = callback;
}

void uv::TcpClient::setMessageCallback(NewMessageCallback callback)
{
    onMessageCallback_ = callback;
}

void uv::TcpClient::setConnectCloseCallback(OnConnectClose callback)
{
    onConnectCloseCallback_ = callback;
}

EventLoop* uv::TcpClient::Loop()
{
    return loop_;
}

int uv::TcpClient::appendToBuffer(const char* data, int size)
{
    if(connection_)
    {
        return connection_->appendToBuffer(data,size);
    }
    return -1;
}

int uv::TcpClient::readFromBuffer(Packet& packet)
{
    if(connection_)
    {
        return connection_->readFromBuffer(packet);
    }
    return -1;
}

void TcpClient::update()
{
    ::uv_tcp_init(loop_->hanlde(), socket_);
    if (tcpNoDelay_)
        ::uv_tcp_nodelay(socket_,1);
    socket_->data = static_cast<void*>(this);
}

void uv::TcpClient::runConnectCallback(bool isSuccess)
{
    if (connectCallback_)
        connectCallback_(isSuccess);
}
