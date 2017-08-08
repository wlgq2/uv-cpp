#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include "uv/TcpClient.h"


class Client : public uv::TcpClient
{
public:
    Client(uv_loop_t* loop)
        :TcpClient(loop)
    {
        setConnectCloseCallback(std::bind(&Client::onConnectClose,this));
    }

    void onConnectClose()
    {
        connect("192.168.141.73",10010);
    }
};
#endif
