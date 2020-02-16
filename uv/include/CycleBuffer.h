/*
Copyright © 2017-2019, orcaer@yeah.net  All rights reserved.

Author: orcaer@yeah.net

Last modified: 2018-10-24

Description: https://github.com/wlgq2/uv-cpp
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
    uint64_t size;
    uint64_t part1;
    uint64_t part2;
};

class ArrayBuffer :public PacketBuffer
{
public:
    ArrayBuffer();
    ~ArrayBuffer();

    //写字节时必须距离读字节一个字节，否则无法区分缓存满/空。
    int append(const char* data, uint64_t size) override;
    int readBufferN(std::string& data, uint64_t N) override;
    int clearBufferN(uint64_t N) override;
    int clear() override;
    uint64_t readSize()  override;

    uint64_t usableSize();
    void usableSizeInfo(SizeInfo& info);
    void readSizeInfo(SizeInfo& info);

private:
    int addWriteIndex(uint64_t size);
    int addReadIndex(uint64_t size);

private:
    uint8_t* buffer_;
    uint64_t writeIndex_;
    uint64_t readIndex_;

};

}
#endif // !  UV_PACKET_H

