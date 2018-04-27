/*
Copyright 2017, orcaer@yeah.net  All rights reserved.

Author: orcaer@yeah.net

Last modified: 2018-4-24

Description: https://github.com/wlgq2/libuv_cpp11
*/

#ifndef  UV_PACKET_H
#define  UV_PACKET_H

#include <string>

//Packet:
//---------------------------------------
//  head  |  size   |  data   |  end   |
// 1 byte | 2 bytes | N bytes | 1 byte |
//---------------------------------------

namespace uv
{

class Packet
{
public:
    Packet();
    ~Packet();

    void fill(const char* data, uint16_t size);
    void update(char* data, uint16_t size);
    void clear();

    const char* getData();
    const uint16_t DataSize();
    const char* Buffer();
    const uint16_t BufferSize();

    static int UnpackDataSize(const uint8_t* data);
    static void PackDataSize(char* data, uint16_t size);
    static int PacketMinSize();

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
    char* buffer_;
    uint16_t bufferSize_;
};
}
#endif