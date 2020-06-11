/*
   Copyright © 2017-2019, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net

   Last modified: 2019-2-21

   Description: https://github.com/wlgq2/uv-cpp
*/

#ifndef UV_ASYNC_H
#define UV_ASYNC_H

#include <memory>
#include <functional>
#include <queue>
#include <mutex>

#include "EventLoop.h"


namespace uv
{

class Async  : public std::enable_shared_from_this<Async>
{
public:
    

    Async(EventLoop* loop);
    virtual ~Async();

    void runInThisLoop(DefaultCallback callback);
    

    void close(DefaultCallback callback);
private:
    std::mutex mutex_;
    uv_async_t* handle_;
    std::queue<DefaultCallback> callbacks_;

    void process();
    static void Callback(uv_async_t* handle);

};


using AsyncPtr = std::shared_ptr<Async>;

}
#endif
