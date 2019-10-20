/*
   Copyright © 2017-2019, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net

   Last modified: 2019-10-20

   Description: https://github.com/wlgq2/uv-cpp
*/

#ifndef UV_UDP_H
#define UV_UDP_H

#include <functional>

#include "EventLoop.h"
#include "SocketAddr.h"

namespace uv
{


class Udp
{
public:
    using OnUdpMessageCallback = std::function<void(SocketAddr&, const char*, unsigned)>;

    Udp(EventLoop* loop);
    virtual ~Udp();

    int bindAndRead(SocketAddr& addr);

    int send(SocketAddr& to, const char* buf, unsigned size);

    void close(DefaultCallback callback);

    void onCloseCompleted();

    void onMessage(const sockaddr* from, const char* data, unsigned size);
    void setMessageCallback(OnUdpMessageCallback callback);

public:
    static void onMesageReceive(uv_udp_t* handle, ssize_t nread, const uv_buf_t* buf, const struct sockaddr* addr, unsigned flags);
    
private:
    SocketAddr::IPV ipv_;
    uv_udp_t* handle_;
    DefaultCallback onClose_;

    OnUdpMessageCallback onMessageCallback_;
};

}
#endif
