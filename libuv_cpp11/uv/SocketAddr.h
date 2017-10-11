/*
Copyright 2017, object_he@yeah.net  All rights reserved.

Author: object_he@yeah.net

Last modified: 2017-9-30

Description:
*/

#ifndef    SOCKET_ADDR_H
#define    SOCKET_ADDR_H

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
        :port(port),
        ipv(ipv)
    {
        if (ipv == Ipv6)
        {
            ::uv_ip6_addr(ip, port, &ipv6);
        }
        else
        {
            ::uv_ip4_addr(ip, port, &ipv4);
        }
    }

    const sockaddr* Addr()
    {
        return (ipv == Ipv6) ? reinterpret_cast<const sockaddr*>(&ipv6) : reinterpret_cast<const sockaddr*>(&ipv4);
    }

    std::string AddrStr()
    {
        return ip + ":" + std::to_string(port);
    }

private:
    std::string ip;
    unsigned short port;
    const IPV ipv;
    sockaddr_in ipv4;
    sockaddr_in6 ipv6;
};

}
#endif
