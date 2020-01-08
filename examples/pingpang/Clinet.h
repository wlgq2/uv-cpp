#ifndef CLIENT_H
#define CLIENT_H


#include <string>
#include "uv/include/uv11.h"

class Client : public uv::TcpClient
{
public:
    Client(uv::EventLoop* loop)
        :TcpClient(loop),
        sockAddr(nullptr)
    {
        setConnectStatusCallback(std::bind(&Client::onConnect,this,std::placeholders::_1));
        setMessageCallback(std::bind(&Client::newMessage,this,std::placeholders::_1,std::placeholders::_2));
    }

    void connectToServer(uv::SocketAddr& addr)
    {
        sockAddr = std::make_shared<uv::SocketAddr>(addr);
        connect(addr);
    }

    void reConnect()
    {
        uv::Timer* timer = new uv::Timer(Loop(), 1000, 0, [this](uv::Timer* timer)
        {
            connect(*(sockAddr.get()));
            timer->close([](uv::Timer* handle)
            {
                delete handle;
            });
        });
        timer->start();
    }
    void sendTestMessage()
    {
        char data[1024] = "test message";
        if (uv::GlobalConfig::BufferModeStatus == uv::GlobalConfig::NoBuffer)
        {
            write(data, (int)sizeof(data));
        }
        else
        {
            uv::Packet packet;
            packet.pack(data, sizeof(data));
            write(packet.Buffer().c_str(), packet.PacketSize());
        }
    }
    void onConnect(TcpClient::ConnectStatus status)
    {
        if (status != TcpClient::ConnectStatus::OnConnectSuccess)
        {
            reConnect();
        }
        else
        {
            sendTestMessage();
        }
    }


    void newMessage(const char* buf,ssize_t size)
    {
        if (uv::GlobalConfig::BufferModeStatus == uv::GlobalConfig::NoBuffer)
        {
            write(buf, (unsigned int)size);
        }
        else  //使用buffer
        {
            auto packetbuf = getCurrentBuf();
            if (nullptr != packetbuf)
            {
                packetbuf->append(buf, static_cast<int>(size));
                uv::Packet packet;
                while (0 == packetbuf->readPacket(packet))
                {
                    write(packet.Buffer().c_str(), (unsigned)packet.PacketSize(), nullptr);
                }
            }
        }
    }

private:
    std::shared_ptr<uv::SocketAddr> sockAddr;
};
#endif
