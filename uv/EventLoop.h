/*
   Copyright 2017, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net
    
   Last modified: 2017-10-10
    
   Description: https://github.com/wlgq2/libuv_cpp11
*/

#ifndef   UV_EVENT_LOOP_H
#define   UV_EVENT_LOOP_H

#include <uv.h>
#include <thread>
#include <atomic>

namespace uv
{
 
class Async;
class EventLoop
{
public:
    enum Mode
    { 
        Default,
        New 
    };
    
    EventLoop();
    ~EventLoop();

    static EventLoop* DefalutLoop();

    int run();
    int runNoWait();
    bool isRunInLoopThread();
    void runInThisLoop(const std::function<void()>& func);
    uv_loop_t* hanlde();

    static const char* GetErrorMessage(int status);

private:
    EventLoop(Mode mode);

    std::thread::id loopThreadId_;
    std::atomic<bool> isRun;
    uv_loop_t* loop_;
    Async* async_;
};

using EventLoopPtr = std::shared_ptr<uv::EventLoop>;
}
#endif  

