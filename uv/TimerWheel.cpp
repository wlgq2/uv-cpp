/*
   Copyright © 2017-2019, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net
    
   Last modified: 2017-10-10
    
   Description: https://github.com/wlgq2/uv-cpp
*/

#include "include/TimerWheel.h"

using namespace uv;
using namespace std;

TimerWheel::TimerWheel(EventLoop* loop)
    :TimerWheel(loop, 0)
{

}

TimerWheel::TimerWheel(EventLoop* loop,unsigned int timeout)
    :index_(0),
    timeoutSec_(timeout),
    timer_(loop,1000,1000,std::bind(&TimerWheel::wheelCallback,this))
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
        wheel_.resize(timeoutSec_);
        timer_.start();
    }
}

void TimerWheel::insert(shared_ptr<TcpConnection> connnection)
{
    if(!timeoutSec_)
        return;
    shared_ptr<ConnectionWrapper> conn = connnection->getWrapper();
    if(conn)
    {
        wheel_[index_].insert(conn);
    }
}

void TimerWheel::insertNew(shared_ptr<TcpConnection> connection)
{
    if(!timeoutSec_)
        return;
    shared_ptr<ConnectionWrapper> wrapper = std::make_shared<ConnectionWrapper>(connection);
    wrapper->setWrapper();
    wheel_[index_].insert(wrapper);
}

void TimerWheel::wheelCallback()
{
    if(!timeoutSec_)
        return;
    if(++index_ ==timeoutSec_)
    {
        index_=0;
    }
    wheel_[index_].clear();
}
