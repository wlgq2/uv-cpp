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

    SocketAddr(const std::string&& ip, unsigned short port, IPV ipv = Ipv4)
        :port_(port),
        ipv_(ipv)
    {
        if (ipv == Ipv6)
        {
            ::uv_ip6_addr(ip.c_str(), port, &ipv6_);
        }
        else
        {
            ::uv_ip4_addr(ip.c_str(), port, &ipv4_);
        }
    }

    SocketAddr(const std::string& ip, unsigned short port, IPV ipv = Ipv4)
        :SocketAddr(std::move(ip),port,ipv)
    {

    }
    const sockaddr* Addr()
    {
        return (ipv_ == Ipv6) ? reinterpret_cast<const sockaddr*>(&ipv6_) : reinterpret_cast<const sockaddr*>(&ipv4_);
    }

    void toStr(std::string& str)
    {
        str =  ip_ + ":" + std::to_string(port_);
    }

    IPV Ipv()
    {
        return ipv_;
    }

    static  void AddrToStr(uv_tcp_t* client, std::string& addrStr, IPV ipv = Ipv4)
    {
        auto inet = (Ipv6 == ipv) ? AF_INET6 : AF_INET;
        struct sockaddr_storage addr;
        int len = sizeof(struct sockaddr_storage);
        ::uv_tcp_getpeername(client, (struct sockaddr *)&addr, &len);

        char ip[64];   
        //windows环境下需要修改NTDDI_VERSION 大于NTDDI_LONGHORN，否则会提示找不到inet_ntop函数。
        if (Ipv6 == ipv)
        {
            struct sockaddr_in6* addr6 = (struct sockaddr_in6 *)&addr;
            std::string str(inet_ntop(inet, (void *)&(addr6->sin6_addr), ip, 64));
            addrStr = str + ":" + std::to_string(htons(addr6->sin6_port));
        }
        else
        {
            struct sockaddr_in *addr4 = (struct sockaddr_in *)&addr;
            std::string str(inet_ntop(inet, (void *)&(addr4->sin_addr), ip, 64));
            addrStr = str + ":" + std::to_string(htons(addr4->sin_port));
        }
        
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
