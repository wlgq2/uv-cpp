/*
Copyright © 2017-2020, orcaer@yeah.net  All rights reserved.

Author: orcaer@yeah.net

Last modified: 2020-3-29

Description: https://github.com/wlgq2/uv-cpp
*/
#include "include/DnsGet.hpp"
#include "include/LogWriter.hpp"

using namespace uv;

DNSGet::DNSGet(uv::EventLoop* loop)
	:loop_(loop),
    callback_(nullptr)
{
    handle_.data = (void*) this;
}

void DNSGet::setOnDNSCallback(OnGetIPAddrCallback callback)
{
    callback_ = callback;
}

int DNSGet::GetIP(std::string& hostname, std::string service )
{
    return uv_getaddrinfo(loop_->handle(), &handle_, DNSGet::onDNSGet, hostname.c_str(), service.c_str(), NULL);
}

int DNSGet::GetIP(std::string&& hostname, std::string service)
{
    return GetIP(hostname, service);
}

void DNSGet::OnCallback(int status, addrinfo* res)
{
    if (nullptr != callback_)
    {
        std::string ip("");
        if (status < 0) {
            callback_(status, ip);
            return;
        }
        ip.resize(32);
#if    _MSC_VER
        if (res->ai_protocol == IPPROTO_IPV4 || res->ai_protocol == IPPROTO_TCP || res->ai_protocol == IPPROTO_IP)
        
#else
        if (res->ai_protocol == IPPROTO_TCP || res->ai_protocol == IPPROTO_IP)
#endif
        {
            uv_ip4_name((struct sockaddr_in*) res->ai_addr, (char*)ip.c_str(), ip.size());

        }
        else if (res->ai_protocol == IPPROTO_IPV6)
        {
            uv_ip6_name((struct sockaddr_in6*) res->ai_addr, (char*)ip.c_str(), ip.size());
        }
        callback_(status, ip);
    }
}

void DNSGet::onDNSGet(uv_getaddrinfo_t* addrInfo, int status, addrinfo* res)
{
    auto ptr = (DNSGet*)(addrInfo->data);
    if (ptr)
    {
        ptr->OnCallback(status,res);
        uv_freeaddrinfo(res);
    }
}

