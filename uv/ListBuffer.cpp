/*
Copyright 2017, orcaer@yeah.net  All rights reserved.

Author: orcaer@yeah.net

Last modified: 2018-4-15

Description: https://github.com/wlgq2/libuv_cpp11
*/

#include "ListBuffer.h"


#include <iostream>
using namespace uv;
using namespace std;

ListBuffer::ListBuffer()
{

}

ListBuffer::~ListBuffer()
{

}

int ListBuffer::append(const char* data, int size)
{
    for (auto i = 0; i < size; i++)
        buffer_.push_back(data[i]);
    return size;
}


int uv::ListBuffer::read(Packet& packet)
{
    while ((!buffer_.empty()) && (Packet::HeadByte != buffer_.front()))
        buffer_.pop_front();
    auto bufSize = buffer_.size();
    if (bufSize <= Packet::PacketMinSize())
    {
        return -1;
    }
    buffer_.pop_front();
    uint8_t sizebuf[2];
    sizebuf[0] = buffer_.front();
    buffer_.pop_front();
    sizebuf[1] = buffer_.front();
    buffer_.pop_front();
    uint16_t size = Packet::UnpackDataSize(sizebuf);

    if (size + Packet::PacketMinSize() > bufSize)
    {
        buffer_.push_front(sizebuf[1]);
        buffer_.push_front(sizebuf[0]);
        buffer_.push_front(Packet::HeadByte);
        return -1;
    }
    char* data = new char[size + Packet::PacketMinSize()];
    data[0] = Packet::HeadByte;
    Packet::PackDataSize(&data[1],(uint16_t) size);

    for (int i = 0; i <= size; i++)
    {
        data[i + Packet::PacketMinSize()-1] = buffer_.front();
        buffer_.pop_front();
    }
    if(static_cast<uint8_t>(data[size+ Packet::PacketMinSize()-1]) != Packet::EndByte)
    {
        delete[] data;
        return -1;
    }
    packet.update(data, size + Packet::PacketMinSize());
    return 0;
}
