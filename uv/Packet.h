/*
Copyright © 2017-2019, orcaer@yeah.net  All rights reserved.

Author: orcaer@yeah.net

Last modified: 2018-7-18

Description: https://github.com/wlgq2/uv-cpp
*/

#ifndef  UV_PACKET_H
#define  UV_PACKET_H

#include <string>
#include "PacketBuffer.h"
//Packet:
//------------------------------------------------
//  head  |  size   | data   |  end   |
// 1 byte | 2 bytes | N bytes| 1 byte |
//------------------------------------------------

namespace uv
{

class Packet
{
public:
    Packet();
    ~Packet();

    static int readFromBuffer(PacketBuffer*, Packet&);

    void pack(const char* data, uint16_t size);

    const char* getData();
    const uint16_t DataSize();
    const std::string& Buffer();
    const uint32_t PacketSize();

    void swap(std::string& str);
    template<typename NumType>
    static void UnpackNum(const uint8_t* data, NumType& num);

    template<typename NumType>
    static void PackNum(char* data, NumType num);

    static uint32_t PacketMinSize();

public:
    enum DataMode
    {
        BigEndian,
        LittleEndian
    };

    static uint8_t HeadByte;
    static uint8_t EndByte;
    static DataMode Mode;

private:
    std::string buffer_;
    uint16_t dataSize_;
};

template<typename NumType>
inline void Packet::UnpackNum(const uint8_t* data, NumType& num)
{
    num = 0;
    auto size = static_cast<int>(sizeof(NumType));
    if (Packet::DataMode::BigEndian == Packet::Mode)
    {
        for (int i = 0; i < size; i++)
        {
            num <<= 8;
            num |= data[i];

        }
    }
    else
    {
        for (int i = size-1; i >= 0; i--)
        {
            num <<= 8;
            num |= data[i];
        }
    }
}

template<typename NumType>
inline void Packet::PackNum(char* data, NumType num)
{
    int size = static_cast<int>(sizeof(NumType));
    if (Packet::DataMode::BigEndian == Packet::Mode)
    {
        for (int i = size-1; i >= 0; i--)
        {
            data[i] = num & 0xff;
            num >>= 8;
        }
    }
    else
    {
        for (int i = 0; i < size; i++)
        {
            data[i] = num & 0xff;
            num >>= 8;
        }
    }
}
}
#endif
