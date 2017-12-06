/*
   Copyright 2017, object_he@yeah.net  All rights reserved.

   Author: object_he@yeah.net 
    
   Last modified: 2017-10-10
    
   Description: 
*/

#ifndef   UV_EVENT_LOOP_H
#define   UV_EVENT_LOOP_H

#include <uv.h>
#include <thread>
#include <atomic>

namespace uv
{
class EventLoop
{
public:
    enum Mode
    { 
        DefaultLoop,
        NewLoop 
    };

    EventLoop(Mode mode = Mode::NewLoop);
    ~EventLoop();

    int run();
    bool isRunInLoopThread();
    uv_loop_t* hanlde();

    static const char* GetErrorMessage(int status);

private:
    std::thread::id loopThreadId_;
    std::atomic<bool> isRun;
    uv_loop_t* loop_;
};

using EventLoopPtr = std::shared_ptr<uv::EventLoop>;
}
#endif  

