/*
   Copyright © 2017-2019, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net

   Last modified: 2020-3-29

   Description: https://github.com/wlgq2/uv-cpp
*/

#ifndef UV_DNS_GET_HPP
#define UV_DNS_GET_HPP

#include <functional>

#include "EventLoop.hpp"
#include "SocketAddr.hpp"

namespace uv
{


class DNSGet
{
public:
	using OnGetIPAddrCallback = std::function<void(int,std::string&)>;

    DNSGet(uv::EventLoop* loop);
    
	void setOnDNSCallback(OnGetIPAddrCallback callback);

	int GetIP(std::string& hostname, std::string service = "");
	int GetIP(std::string&& hostname, std::string service = "");

    
private:
	EventLoop* loop_;
	OnGetIPAddrCallback callback_;
    uv_getaddrinfo_t handle_;

    void OnCallback(int status, addrinfo* res);
    static void onDNSGet(uv_getaddrinfo_t* addrInfo, int status, struct addrinfo* res);

};

}
#endif
