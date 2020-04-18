/*
   Copyright © 2017-2019, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net

   Last modified: 2020-3-29

   Description: https://github.com/wlgq2/uv-cpp
*/

#ifndef UV_DNS_GET_H
#define UV_DNS_GET_H

#include <functional>

#include "EventLoop.h"
#include "SocketAddr.h"

namespace uv
{


class DNSGet
{
public:
	using OnGetIPAddrCallback = std::function<void(int,std::string&)>;

    DNSGet(uv::EventLoop* loop);
    
	void setOnDNSCallback(OnGetIPAddrCallback callback);

	int GetIP(std::string& ip, std::string service = "");
	int GetIP(std::string&& ip, std::string service = "");

    void OnCallback(int status, addrinfo* res);
private:
	EventLoop* loop_;
	OnGetIPAddrCallback callback_;
    uv_getaddrinfo_t handle_;


    static void onDNSGet(uv_getaddrinfo_t* addrInfo, int status, struct addrinfo* res);

};

}
#endif
