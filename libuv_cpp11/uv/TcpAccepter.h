/*
   Copyright 2017, object_he@yeah.net  All rights reserved.

   Author: object_he@yeah.net 
    
   Last modified: 2017-8-8
    
   Description: 
*/

#ifndef TCP_ACCEPTER_H
#define TCP_ACCEPTER_H

#include <uv.h>
#include <functional>

namespace uv
{

using NewConnectionCallback  =    std::function<void(uv_loop_t* ,uv_tcp_t*)> ;

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
