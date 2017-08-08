#ifndef TCP_ACCEPTER_H
#define TCP_ACCEPTER_H

#include <uv.h>
#include <functional>

namespace uv
{

typedef   std::function<void(uv_loop_t* ,uv_tcp_t*)> NewConnectionCallback;

class TcpAccepter
{
public:
    TcpAccepter(uv_loop_t* loop,const char* ip,int port);
    virtual ~TcpAccepter();

    void listen();
    bool isListen();
    void setNewConnectinonCallback( NewConnectionCallback callback);

    uv_loop_t* getLoop();
    void onNewConnect(uv_tcp_t* client);

private:
    bool listened;
    uv_loop_t* loop;
    NewConnectionCallback newConnectionCallback;

    uv_tcp_t server;

};

}

#endif
