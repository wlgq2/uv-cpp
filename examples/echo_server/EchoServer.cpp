/*
    Copyright © 2017-2019, orcaer@yeah.net  All rights reserved.

    Author: orcaer@yeah.net

    Last modified: 2018-4-18

    Description: https://github.com/wlgq2/uv-cpp
*/

#include    <cstring>
#include    <iostream>

#include    "EchoServer.h"
#include    "uv/include/uv11.h"

using namespace uv;
using namespace std;

EchoServer::EchoServer(EventLoop* loop)
    :TcpServer(loop)
{
    setMessageCallback(std::bind(&EchoServer::newMessage,this,placeholders::_1,placeholders::_2,placeholders::_3));
}

void EchoServer::newMessage(shared_ptr<TcpConnection> connection,const char* buf,ssize_t size)
{
    //不使用buffer
    if (uv::GlobalConfig::BufferModeStatus == uv::GlobalConfig::NoBuffer)
    {
        //std::cout << "reserve data :" << std::string(buf, size) << std::endl;
#if       1   //直接发送
        connection->write(buf, size, nullptr);
#else     //调用write in loop接口
        //实质会直接调用write，并不需要memcpy。
        //writeInLoop需要数据在回调中释放。
        char* data = new  char[size]();
        memcpy(data, buf, size);
        connection->writeInLoop(data, size,
            [this](WriteInfo& info)
        {
            //write message error.
            if (0 != info.status)
            {
                cout << "Write error ：" << EventLoop::GetErrorMessage(info.status) << endl;
            }
            delete[] info.buf;
        });
#endif
    }
    else  //使用buffer
    {
        Packet packet;
        auto packetbuf = connection->getPacketBuffer();
        if (nullptr != packetbuf)
        {
            packetbuf->append(buf, static_cast<int>(size));
            //循环读取buffer
            while (0 == packetbuf->readPacket(packet))
            {
                std::cout << "reserve data "<< packet.DataSize()<<":" << packet.getData() << std::endl;
                connection->write(packet.Buffer().c_str(), packet.PacketSize(), nullptr);
            }
        }
    }
}
