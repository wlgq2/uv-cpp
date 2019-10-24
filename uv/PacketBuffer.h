/*
Copyright © 2017-2019, orcaer@yeah.net  All rights reserved.

Author: orcaer@yeah.net

Last modified: 2019-10-24

Description: https://github.com/wlgq2/uv-cpp
*/

#ifndef    UV_PACKET_BUFFER_H
#define    UV_PACKET_BUFFER_H

#include   <functional>
#include   <string>
#include   "Packet.h"

namespace uv
{

using ReadBufFunc = std::function<int(std::string&)>;
class PacketBuffer
{

public:
    virtual int append(const char* data, int size) = 0;
    virtual int readPacket(Packet& packet) = 0;

    int read(std::string& data)
    {
        if (readbufCallback_)
            return readbufCallback_(data);
    }
    void setReadFunc(ReadBufFunc callback)
    {
        readbufCallback_ = callback;
    }
private:
    ReadBufFunc readbufCallback_;
};

}

#endif // ! UV_PACKET_BUFFER_H

