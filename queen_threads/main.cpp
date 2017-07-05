#include <iostream>
#include <chrono>
#include <ratio>
#include <condition_variable>

#include "ThreadPool.h"
#include "Queen.h"

using namespace std;
using namespace std::chrono;

int main(void)
{
    int len = 15;
    cout<<"solve queen length: "<<len<<endl;

#if    0
    /*
    单线程递归N皇后，15个皇后大约28秒
    */

    //获得初始时间。
    auto timePoint1 = time_point_cast<duration<int,std::ratio<1>>>(system_clock::now());
    int rst[30];
    //创建皇后类
    Queen queen(len,rst);
    //从第0行第0列开始递归
    queen.solve(0);
    //打印计算结果
    cout<<queen.getResultCnt()<<endl;
    //获得结束时间
    auto timePoint2 = time_point_cast<duration<int,std::ratio<1>>>(system_clock::now());
    cout<<timePoint2.time_since_epoch().count()-timePoint1.time_since_epoch().count()<<endl;
#else

    /*
    多线程递归N皇后，15皇后约8秒
    */
    
    //获取时间
    auto timePoint1 = time_point_cast<duration<int, std::ratio<1>>>(system_clock::now());
    //创建线程池
    ThreadPool pool;
    //设置皇后个数
    pool.setQueueCnt(len);
    //设置线程个数，并运行线程。
    pool.runAllThread(4);

    pool.join();

    auto timePoint2 = time_point_cast<duration<int, std::ratio<1>>>(system_clock::now());
    cout << timePoint2.time_since_epoch().count() - timePoint1.time_since_epoch().count() << endl;
#endif

    system("pause");
    return 0;
}
