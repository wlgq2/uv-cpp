/*
   Copyright 2017, object_he@yeah.net  All rights reserved.

   Author: object_he@yeah.net 
    
   Last modified: 2017-8-8
    
   Description: 
*/

#ifndef   TIMER_WHEEL_H
#define   TIMER_WHEEL_H

#include <vector>
#include <set>
#include <memory>
#include "uv/Timer.h"
#include "uv/TcpConnection.h"

namespace uv
{

//algorithm complexity  o(1).

class  ConnectionElement : public std::enable_shared_from_this<ConnectionElement>
{
public:
    ConnectionElement(std::shared_ptr<TcpConnection> conn)
        :connection(conn)
    {

    }

    ~ConnectionElement()
    {
        std::shared_ptr<TcpConnection> conn = connection.lock();
        if(conn)
        {
            conn->onClose();
        }
    }

private:
    std::weak_ptr<TcpConnection> connection;
};


class TimerWheel
{
public:
    TimerWheel(uv_loop_t* loop);
    TimerWheel(uv_loop_t* loop,unsigned int timeout);
    void setTimeout(unsigned int );
    void start();

    void insert(std::shared_ptr<TcpConnection> connnection);
    void insertNew(std::shared_ptr<TcpConnection> connection);
private:
    unsigned int index;
    unsigned int timeoutSec;
    Timer timer;

    std::vector< std::set< std::shared_ptr<ConnectionElement>>> wheel;

    void wheelCallback();

};

}
#endif
