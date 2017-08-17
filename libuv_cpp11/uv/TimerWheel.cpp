/*
   Copyright 2017, object_he@yeah.net  All rights reserved.

   Author: object_he@yeah.net 
    
   Last modified: 2017-8-14
    
   Description: 
*/

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
    if(!timeoutSec)
        return;
    shared_ptr<ConnectionElement> conn = connnection->Element().lock();
    if(conn)
    {
        wheel[index].insert(conn);
    }
}


void TimerWheel::insertNew(shared_ptr<TcpConnection> connection)
{
    if(!timeoutSec)
        return;
    shared_ptr<ConnectionElement> conn(new ConnectionElement(connection));
    connection->setElement(conn);
    wheel[index].insert(conn);
}

void TimerWheel::wheelCallback()
{
    if(!timeoutSec)
        return;
    if(++index ==timeoutSec)
    {
        index=0;
    }
    wheel[index].clear();
}