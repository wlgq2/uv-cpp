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
#include   <memory>

#include   "LogWriter.h"
#include   "GlobalConfig.h"

namespace uv
{
class Packet;
class PacketBuffer
{

public:
    virtual ~PacketBuffer(){}

    virtual int append(const char* data, uint64_t size) = 0;
    virtual int readBufferN(std::string& data, uint64_t N) = 0;
    virtual int clearBufferN(uint64_t N) = 0;
    virtual int clear() = 0;
    virtual uint64_t readSize() = 0;

    int readString(std::string& out)
    {
        if (nullptr != GlobalConfig::ReadBufferString)
            return GlobalConfig::ReadBufferString(this, out);
        uv::LogWriter::Instance()->error("not defined packet parse func.");
        return -1;
    }

    int readPacket(Packet& out)
    {
        if (nullptr != GlobalConfig::ReadBufferPacket)
            return GlobalConfig::ReadBufferPacket(this, out);
        uv::LogWriter::Instance()->error("not defined packet parse func.");
        return -1;
    }

    int readGeneric(void* out)
    {
        if (nullptr != GlobalConfig::ReadBufferVoid)
            return GlobalConfig::ReadBufferVoid(this, out);
        uv::LogWriter::Instance()->error("not defined packet parse func.");
        return -1;
    }
};

using PacketBufferPtr = std::shared_ptr<PacketBuffer>;
}

#endif // ! UV_PACKET_BUFFER_H

