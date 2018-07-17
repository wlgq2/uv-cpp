/*
Copyright 2017, orcaer@yeah.net  All rights reserved.

Author: orcaer@yeah.net

Last modified: 2018-7-18

Description: https://github.com/wlgq2/libuv_cpp11
*/

#include  "Packet.h"

using namespace uv;


uint8_t Packet::HeadByte = 0x7e;
uint8_t Packet::EndByte = 0xe7;
Packet::DataMode Packet::Mode = Packet::DataMode::LittleEndian;

Packet::Packet()
    :reserve_(0),
    buffer_(nullptr),
    bufferSize_(0)
{

}

uv::Packet::~Packet()
{
    clear();
}

void uv::Packet::fill(const char* data, uint16_t size)
{
    clear();

    bufferSize_ = size + PacketMinSize();
    buffer_ = new char[bufferSize_];

    buffer_[0] = HeadByte;
    PackNum(&buffer_[1],size);
    PackNum(&buffer_[3], reserve_);

    std::copy(data, data + size, buffer_ + sizeof(HeadByte) + sizeof(bufferSize_)+sizeof(reserve_));
    buffer_[size + PacketMinSize()-1] = EndByte;
}

void uv::Packet::update(char* data, uint16_t size)
{
    clear();
    UnpackNum((const uint8_t*)(&data[3]), reserve_);
    buffer_ = data;
    bufferSize_ = size;
}


void uv::Packet::clear()
{
    if (0 !=bufferSize_)
    {
        delete[] buffer_;
        bufferSize_ = 0;
    }
}

const char* uv::Packet::getData()
{
    return buffer_+sizeof(HeadByte)+sizeof(bufferSize_)+sizeof(reserve_);
}

const uint16_t uv::Packet::DataSize()
{
    return bufferSize_ - PacketMinSize();
}

const char * uv::Packet::Buffer()
{
    return buffer_;
}

const uint16_t uv::Packet::BufferSize()
{
    return bufferSize_;
}


uint32_t uv::Packet::PacketMinSize()
{
    return 8;
}
