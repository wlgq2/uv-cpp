/*
   Copyright 2017, object_he@yeah.net  All rights reserved.

   Author: object_he@yeah.net 
    
   Last modified: 2017-10-10
    
   Description: 
*/

#include "TimerWheel.h"

using namespace uv;
using namespace std;

TimerWheel::TimerWheel(EventLoop* loop)
    :TimerWheel(loop,0)
{

}

TimerWheel::TimerWheel(EventLoop* loop,unsigned int timeout)
    :index_(0),
    timeoutSec_(timeout),
    timer_(loop,1000,1000,std::bind(&TimerWheel::wheelCallback,this,std::placeholders::_1, std::placeholders::_2),nullptr)
{

}

void TimerWheel::setTimeout(unsigned int second)
{
    timeoutSec_ = second;
}

void TimerWheel::start()
{
    if(timeoutSec_)
    {
        wheel.resize(timeoutSec_);
        timer_.start();
    }
}

void TimerWheel::insert(shared_ptr<TcpConnection> connnection)
{
    if(!timeoutSec_)
        return;
    shared_ptr<ConnectionElement> conn = connnection->Element().lock();
    if(conn)
    {
        wheel[index_].insert(conn);
    }
}


void TimerWheel::insertNew(shared_ptr<TcpConnection> connection)
{
    if(!timeoutSec_)
        return;
    shared_ptr<ConnectionElement> conn(new ConnectionElement(connection));
    connection->setElement(conn);
    wheel[index_].insert(conn);
}

void TimerWheel::wheelCallback(Timer<void*>*,void*)
{
    if(!timeoutSec_)
        return;
    if(++index_ ==timeoutSec_)
    {
        index_=0;
    }
    wheel[index_].clear();
}
