#include "EchoServer.h"
#include <cstring>

using namespace uv;
using namespace std;

EchoServer::EchoServer(uv_loop_t* loop,int port ,const char* ip)
    :TcpServer(loop,port,ip)
{
    setMessageCallback(std::bind(&EchoServer::newMessage,this,placeholders::_1,placeholders::_2,placeholders::_3));
}

void EchoServer::newMessage(shared_ptr<TcpConnection> connection,const char* buf,ssize_t size)
{
#if    0
    connection->write(buf,size,nullptr);

#else
    char* data =  new  char [size]();
    memcpy(data, buf, size);
    connection->writeInLoop(data, size,
    [](char* buf,ssize_t size)
    {
        delete [] buf;
    });
#endif
}
