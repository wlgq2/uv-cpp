#include <iostream>
#include "ThreadPool.h"


using namespace std;

ThreadPool::ThreadPool()
    :completed(false),
    queueCnt(0),
    started(false),
    threadCount(0),
    threadIndex(0),
    completCnt(0)
{
}

void ThreadPool::completOneThread()
{
    //原子变量
    completCnt++;
    if(completCnt == threadCount)
    {
        int sum = 0;
        for(auto thread:threads)
        {
            sum += thread->getResultCnt();
            cout<<"thread : "<<thread->getResultCnt()<<endl;
        }
        cout<<"threads count :"<<sum<<endl;

    }
}

bool ThreadPool::isCompleted()
{
    return completed;
}
void ThreadPool::join()
{
    for (auto thread : threads)
    {
        thread->join();
    }
}

void ThreadPool::setQueueCnt(uint16_t cnt)
{
    queueCnt = cnt;
}

void ThreadPool::runAllThread()
{
    for(int i=0;i<threadCount;i++)
    {
        std::shared_ptr<Thread> thread(new Thread(this,queueCnt,i));
        threads.push_back(thread);

    }
    started = true;
    
    Thread::startAllThread();
}

void ThreadPool::runAllThread(int num)
{
    setThreadCount(num);
    runAllThread();
}

bool ThreadPool::isStarted()
{
    return started;
}

void ThreadPool::setThreadCount(uint16_t num)
{
    threadCount = num;
}

uint16_t ThreadPool::getThreadCount()
{
    return threadCount;
}
