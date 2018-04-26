/*
Copyright 2017, orcaer@yeah.net  All rights reserved.

Author: orcaer@yeah.net

Last modified: 2018-4-24

Description: https://github.com/wlgq2/libuv_cpp11
*/

#ifndef    UV_PACKET_BUFFER_H
#define    UV_PACKET_BUFFER_H

#include   "Packet.h"

namespace uv
{

class PacketBuffer
{

public:
    virtual int append(const char* data, int size) = 0;
    virtual int read(Packet& packet) = 0;

};

}

#endif // ! UV_PACKET_BUFFER_H

