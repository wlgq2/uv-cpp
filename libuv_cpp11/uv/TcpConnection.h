/*
   Copyright 2017, object_he@yeah.net  All rights reserved.

   Author: object_he@yeah.net 
    
   Last modified: 2017-8-8
    
   Description: 
*/

#ifndef PROXY_CONNECTION_H
#define PROXY_CONNECTION_H

#include <iostream>
#include <memory>

#include <uv.h>
#include <chrono>
#include <functional>
#include <atomic>


#define        TIME_OUT_SECONDS       40
#define        TIME_SECOND_NOW         std::chrono::time_point_cast<SecondType>(std::chrono::system_clock::now())
#define        TIME_M_SENCOND_NOW      std::chrono::time_point_cast<MSecondType>(std::chrono::system_clock::now())

namespace uv
{
//timeout ctrl.

struct write_req_t
{
    uv_write_t req;
    uv_buf_t buf;
} ;

typedef void (* AfterWriteCallback)(char* buf,unsigned int size);

class TcpServer;
class ConnectionElement;

class TcpConnection : public std::enable_shared_from_this<TcpConnection>
{

public :
    TcpConnection(uv_loop_t* loop,TcpServer* server,uv_tcp_t* client);
    virtual ~TcpConnection();
    void onMessage(const char* buf,ssize_t size);
    void onClose();

    void write(const char* buf,unsigned int size,AfterWriteCallback callback);
    void writeInLoop(const char* buf,unsigned int size,AfterWriteCallback callback);
    typedef  std::chrono::duration<int, std::ratio<1>> SecondType;


    void setElement(std::shared_ptr<ConnectionElement> conn);
    std::weak_ptr<ConnectionElement> Element();

    static void  onMesageReceive(uv_stream_t* client, ssize_t nread, const uv_buf_t* buf);
private :
    uv_loop_t* loop;
    TcpServer* server;
    uv_tcp_t* client;

    std::chrono::time_point<std::chrono::system_clock,SecondType> activeTimePoint;

    uv_async_t asyncWriteHandle;

    std::weak_ptr<ConnectionElement> element;

};

}
#endif
