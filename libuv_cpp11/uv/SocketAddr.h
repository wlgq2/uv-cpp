/*
Copyright 2017, object_he@yeah.net  All rights reserved.

Author: object_he@yeah.net

Last modified: 2017-9-30

Description:
*/

#ifndef    UV_SOCKET_ADDR_H
#define    UV_SOCKET_ADDR_H

#include <string>

#include <uv.h>

namespace uv
{ 


class  SocketAddr
{
public:
    enum IPV
    {
        Ipv4,
        Ipv6
    };

    SocketAddr(const char* ip, unsigned short port, IPV ipv = Ipv4)
        :port_(port),
        ipv_(ipv)
    {
        if (ipv == Ipv6)
        {
            ::uv_ip6_addr(ip, port, &ipv6_);
        }
        else
        {
            ::uv_ip4_addr(ip, port, &ipv4_);
        }
    }

    const sockaddr* Addr()
    {
        return (ipv_ == Ipv6) ? reinterpret_cast<const sockaddr*>(&ipv6_) : reinterpret_cast<const sockaddr*>(&ipv4_);
    }

    std::string AddrStr()
    {
        return ip_ + ":" + std::to_string(port_);
    }

private:
    std::string ip_;
    unsigned short port_;
    const IPV ipv_;
    sockaddr_in ipv4_;
    sockaddr_in6 ipv6_;
};

}
#endif
