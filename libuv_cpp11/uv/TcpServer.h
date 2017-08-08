#ifndef PT_SERVER_H
#define PT_SERVER_H

#include <iostream>
#include <functional>
#include <memory>
#include <set>
#include <map>

#include "uv/TcpAccepter.h"
#include "uv/TcpConnection.h"
#include "uv/TimerWheel.h"


namespace uv
{

typedef std::function<void (std::shared_ptr<TcpConnection>,const char* buf,ssize_t size)>  OnMessageCallback;

//no thread safe.
class TcpServer
{
public:
    TcpServer(uv_loop_t* loop,int port ,const char* ip = (char*)"0.0.0.0");
    virtual ~TcpServer();
    void start();

    void addConnnection(uv_tcp_t* client,std::shared_ptr<TcpConnection> proxy);
    void removeConnnection(uv_tcp_t* client);
    std::shared_ptr<TcpConnection> getConnnection(uv_tcp_t* client);
    void closeConnection(uv_tcp_t* client);

    void onMessage(std::shared_ptr<TcpConnection> connection,const char* buf,ssize_t size);
    void setMessageCallback(OnMessageCallback callback);

    void write(std::shared_ptr<TcpConnection> connection,const char* buf,unsigned int size);
    void write(uv_tcp_t* client,const char* buf,unsigned int size);
    void writeInLoop(std::shared_ptr<TcpConnection> connection,const char* buf,unsigned int size,AfterWriteCallback callback);
    void writeInLoop(uv_tcp_t* client,const char* buf,unsigned int size,AfterWriteCallback callback);

    void setTimeout(unsigned int);
private:
    std::shared_ptr <TcpAccepter> accetper;
    std::map<uv_tcp_t* ,std::shared_ptr<TcpConnection>>  connnections;


    OnMessageCallback onMessageCallback;
    TimerWheel timerWheel;

};


}
#endif
