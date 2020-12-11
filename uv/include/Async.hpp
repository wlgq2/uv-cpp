/*
   Copyright © 2017-2020, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net

   Last modified:  2020-10-6

   Description: https://github.com/wlgq2/uv-cpp
*/

#ifndef UV_ASYNC_HPP
#define UV_ASYNC_HPP

#include <memory>
#include <functional>
#include <queue>
#include <mutex>

#include "EventLoop.hpp"


namespace uv
{

class Async  : public std::enable_shared_from_this<Async>
{
public:
    using OnCloseCompletedCallback = std::function<void(Async*)>;
    Async(EventLoop* loop);
    void  init();
    virtual ~Async();

    void runInThisLoop(DefaultCallback callback);

    void close(OnCloseCompletedCallback callback);
    EventLoop* Loop();
private:
    EventLoop* loop_;
    std::mutex mutex_;
    uv_async_t* handle_;
    std::queue<DefaultCallback> callbacks_;
    OnCloseCompletedCallback onCloseCompletCallback_;
    void process();
    static void Callback(uv_async_t* handle);
    void onCloseCompleted();

};


using AsyncPtr = std::shared_ptr<Async>;

}
#endif
