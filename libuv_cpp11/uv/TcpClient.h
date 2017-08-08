#ifndef   TCP_CLIENT_H
#define   TCP_CLIENT_H

#include  <uv.h>
#include  <functional>

namespace uv
{

typedef std::function<void(bool)>  ConnectCallback;
typedef std::function<void(const char* buf,ssize_t size)>  NewMessageCallback;
typedef std::function<void()> OnConnectClose;

class TcpClient
{
public:
    TcpClient(uv_loop_t* loop);
    ~TcpClient();

    void connect(const char* ip, unsigned short port);

    void onConnect(bool successed);
    void onConnectClose();
    void onMessage(const char* buf,ssize_t size);

    void setConnectCallback(ConnectCallback callback)
    {
        connectCallback = callback;
    }
    void setMessageCallback(NewMessageCallback callback)
    {
        onMessageCallback = callback;
    }
    void setConnectCloseCallback(OnConnectClose callback)
    {
        onConnectCloseCallback = callback;
    }

    static void  onMesageReceive(uv_stream_t* client, ssize_t nread, const uv_buf_t* buf);

private:
    bool connected;
    uv_loop_t* loop;
    uv_tcp_t* socket;
    uv_connect_t* connect_;
    struct sockaddr_in dest;
    ConnectCallback connectCallback;
    NewMessageCallback onMessageCallback;
    OnConnectClose onConnectCloseCallback;

    void updata();
};

}
#endif
