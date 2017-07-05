#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <vector>
#include <memory>
#include <atomic>
#include <condition_variable>
#include <mutex>
#include "Thread.h"


class ThreadPool
{
public:
    ThreadPool();

    void runAllThread();
    void runAllThread(int num );
    bool isStarted();
    void setThreadCount(uint16_t num);
    void setQueueCnt(uint16_t cnt);
    uint16_t getThreadCount();

    void completOneThread();

    bool isCompleted();
    void join();
private:
    bool completed;
    uint16_t queueCnt;
    bool started;
    uint16_t threadCount;
    uint16_t threadIndex;
    std::vector<std::shared_ptr<Thread>> threads;

    std::atomic<unsigned> completCnt;

};



#endif // AGILNET_NET_IOEVENTLOOPTHREADPOOL
