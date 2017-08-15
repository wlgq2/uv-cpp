#ifndef LOOPTHREAD_H
#define LOOPTHREAD_H

#include <thread>
#include <memory>
#include <mutex>
#include <functional>
#include <condition_variable>

class ThreadPool;

class Thread
{
public :
    Thread(ThreadPool* pool,int queueCnt = 0,int id = 0);
    virtual ~Thread();

    static std::thread::id getNowThreadId();
    int getResultCnt();
    virtual void run();
    static void startAllThread();

    void join();
protected:
    void sleepSeconds(int seconds);
private:
    ThreadPool* pool;
    //线程编号
    int id;
    std::shared_ptr<std::thread> thread;
    static bool isStarted;
    static std::mutex mutex;
    static std::condition_variable condition;
    //皇后个数
    int queueCnt;
    //解数量
    int resultCnt;
    //皇后最大个数
    static const unsigned int MaxLength;

};



#endif // THREAD_H_INCLUDED
