/*
   Copyright © 2017-2019, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net

   Last modified: 2019-9-20

   Description: https://github.com/wlgq2/uv-cpp
*/


#ifndef RPC_CTRL_H
#define RPC_CTRL_H


#include <string>
#include <mutex>
#include <condition_variable>

#include "RpcClient.h"



class RpcCtrl
{
public:
    RpcCtrl(uv::SocketAddr& addr);
	virtual ~RpcCtrl();

	void sum(Req& req,Resp& resp);
    void onResp(Resp& resp);

private:
    void backRun();

private:
    RpcClient* client_;
    uv::SocketAddr addr_;
    Resp resp_;
    std::mutex mutex_;
    std::condition_variable condition_;
    bool ready_;
};

#endif
