#include "TimerWheel.h"

using namespace uv;
using namespace std;

TimerWheel::TimerWheel(uv_loop_t* loop)
    :TimerWheel(loop,0)
{

}

TimerWheel::TimerWheel(uv_loop_t* loop,unsigned int timeout)
    :index(0),
    timeoutSec(timeout),
    timer(loop,1000,1000,std::bind(&TimerWheel::wheelCallback,this))
{

}

void TimerWheel::setTimeout(unsigned int timeout)
{
    timeoutSec = timeout;
}

void TimerWheel::start()
{
    if(timeoutSec)
    {
        wheel.resize(timeoutSec);
        timer.start();
    }
}

void TimerWheel::insert(shared_ptr<TcpConnection> connnection)
{
    shared_ptr<ConnectionElement> conn = connnection->Element().lock();
    if(conn)
    {
        wheel[index].insert(conn);
    }
}


void TimerWheel::insertNew(shared_ptr<TcpConnection> connection)
{
    shared_ptr<ConnectionElement> conn(new ConnectionElement(connection));
    connection->setElement(conn);
    wheel[index].insert(conn);
}

void TimerWheel::wheelCallback()
{
    if(++index ==timeoutSec)
    {
        index=0;
    }
    wheel[index].clear();
}
