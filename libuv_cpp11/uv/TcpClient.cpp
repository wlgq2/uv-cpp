#include <iostream>
#include "uv/TcpClient.h"

using namespace uv;
using namespace std;


TcpClient::TcpClient(uv_loop_t* loop)
    :loop(loop),
    socket(new uv_tcp_t()),
    connect_(new uv_connect_t()),
    connectCallback(nullptr),
    onMessageCallback(nullptr),
    onConnectCloseCallback(nullptr)
{
    ::uv_tcp_init(loop, socket);
    socket->data = (void*)this;
}

TcpClient::~TcpClient()
{
    delete socket;
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
            cout << "连接失败" << endl;
            handle->onConnect(false);
            return;
        }

        ::uv_read_start(req->handle,
        [](uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf)
        {
            buf->base = new char[suggested_size];
            buf->len = suggested_size;
        },
        &TcpClient::onMesageReceive);

        handle->onConnect(true);

    });
}

void TcpClient::onConnect(bool successed)
{
    if(connectCallback)
        connectCallback(successed);
}
void TcpClient::onConnectClose()
{
    updata();
    if(onConnectCloseCallback)
        onConnectCloseCallback();
}
void TcpClient::onMessage(const char* buf,ssize_t size)
{
    if(onMessageCallback)
        onMessageCallback(buf,size);
}

void  TcpClient::onMesageReceive(uv_stream_t* client, ssize_t nread, const uv_buf_t* buf)
{
    auto handle = (TcpClient*)(client->data);
    if (nread > 0)
    {
        handle->onMessage(buf->base,nread);
        delete[](buf->base);
        return;
    }
    else if (nread < 0)
    {
        if (nread != UV_EOF)
            cout << "Read error" << uv_err_name(nread) << endl;

        cout << "连接断开" << endl;
        delete[](buf->base);
        uv_shutdown_t* sreq = new uv_shutdown_t;

        ::uv_shutdown(sreq, (uv_stream_t*)client,
        [](uv_shutdown_t* req, int status)
        {
            ::uv_close((uv_handle_t*)req->handle,
            [](uv_handle_t* peer)
            {
                auto handle = (TcpClient*)(peer->data);
                handle->onConnectClose();
            });
            delete req;
        });
    }
    else
    {
        delete[](buf->base);
    }

}

void TcpClient::updata()
{
    ::uv_tcp_init(loop, socket);
}
