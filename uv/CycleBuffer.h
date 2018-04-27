/*
Copyright 2017, orcaer@yeah.net  All rights reserved.

Author: orcaer@yeah.net

Last modified: 2018-4-27

Description: https://github.com/wlgq2/libuv_cpp11
*/
#ifndef   UV_CYCLE_BUFFER_H
#define   UV_CYCLE_BUFFER_H

#include  "PacketBuffer.h"

//ArrayBuffer(cycle)
//---------------------------------------
//  Null  |   byte   |  byte   |  Null 
//---------------------------------------
//        ↑                      ↑
//   read position           write position

//              ↓can not write
//---------------------------------------
//  byte   |   byte   |  byte   |  byte 
//---------------------------------------
//         ↑          ↑
//   write position  read position

//not thread safe.

namespace uv
{

struct SizeInfo
{
    int size;
    int part1;
    int part2;
};
 
class ArrayBuffer :public PacketBuffer
{
public:
    ArrayBuffer();
    ~ArrayBuffer();

    //写字节时必须距离读字节一个字节，否则无法区分缓存满/空。
    int append(const char* data,int size) override;
    int read(Packet& packet) override;
    
    int usableSize();
    void usableSizeInfo(SizeInfo& info);
    int readSize();
    void readSizeInfo(SizeInfo& info);

public:
    static const uint32_t BufferSize;

private:
    int addWriteIndex(uint32_t size);
    int addReadIndex(uint32_t size);

private:
    uint8_t* buffer_;
    uint32_t writeIndex_;
    uint32_t readIndex_;

};

}
#endif // !  UV_PACKET_H

