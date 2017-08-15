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
    connection->write(buf,size,nullptr);

#if   0
    char temp[] = {"hello world"};
    char* data =  new  char [11]();
    memcpy(data,temp,11);
    connection->writeInLoop(data,11,
    [](char* buf,unsigned int size)
    {
        delete [] buf;
    });
#endif
}
