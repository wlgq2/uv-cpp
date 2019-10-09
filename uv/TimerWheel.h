/*
   Copyright © 2017-2019, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net
    
   Last modified: 2017-10-10
    
   Description: https://github.com/wlgq2/uv-cpp
*/

#ifndef   UV_TIMER_WHEEL_H
#define   UV_TIMER_WHEEL_H

#include <vector>
#include <set>
#include <memory>
#include "Timer.h"
#include "TcpConnection.h"

namespace uv
{

//algorithm complexity  o(1).

class  ConnectionElement : public std::enable_shared_from_this<ConnectionElement>
{
public:
    ConnectionElement(TcpConnectionPtr connection)
        :connection_(connection)
    {

    }

    ~ConnectionElement()
    {
        TcpConnectionPtr connection = connection_.lock();
        if(connection)
        {
            connection->onSocketClose();
        }
    }

private:
    std::weak_ptr<TcpConnection> connection_;
};


class TimerWheel
{
public:
    TimerWheel(EventLoop* loop);
    TimerWheel(EventLoop* loop,unsigned int timeout);
    void setTimeout(unsigned int );
    void start();

    void insert(TcpConnectionPtr connnection);
    void insertNew(TcpConnectionPtr connection);
private:
    unsigned int index_;
    unsigned int timeoutSec_;
    Timer timer_;

    std::vector< std::set< std::shared_ptr<ConnectionElement>>> wheel;

    void wheelCallback();

};

}
#endif
