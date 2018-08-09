/*
Copyright 2017, orcaer@yeah.net  All rights reserved.

Author: orcaer@yeah.net

Last modified: 2018-8-9

Description: https://github.com/wlgq2/libuv_cpp11
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
        Ipv4 = 0,
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
    std::string toStr()
    {
        std::string str =  ip_ + ":" + std::to_string(port_);
        return str;
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

        
        //windows环境下需要修改NTDDI_VERSION 大于NTDDI_LONGHORN，否则会提示找不到inet_ntop函数。
        if (Ipv6 == ipv)
        {
            char ip[64];
            struct sockaddr_in6* addr6 = (struct sockaddr_in6 *)&addr;
#if    _MSC_VER
            DWORD size = sizeof (ip);
            WSAAddressToString((LPSOCKADDR)addr6, sizeof(sockaddr_in6), NULL, ip, &size);
            addrStr = std::string(ip);
#else
            std::string str(inet_ntop(inet, (void *)&(addr6->sin6_addr), ip, 64));
            addrStr = str + ":" + std::to_string(htons(addr6->sin6_port));
#endif
        }
        else
        {
            struct sockaddr_in *addr4 = (struct sockaddr_in *)&addr;
            std::string str(inet_ntoa(addr4->sin_addr));
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
