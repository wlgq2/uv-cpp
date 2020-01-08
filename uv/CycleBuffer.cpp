/*
Copyright © 2017-2019, orcaer@yeah.net  All rights reserved.

Author: orcaer@yeah.net

Last modified: 2019-10-24

Description: https://github.com/wlgq2/uv-cpp
*/
#include "include/CycleBuffer.h"
#include "include/GlobalConfig.h"

using namespace uv;

uv::ArrayBuffer::ArrayBuffer()
    :writeIndex_(0),
    readIndex_(0)
{
    buffer_ = new uint8_t[GlobalConfig::GlobalConfig::CycleBufferSize];
}

uv::ArrayBuffer::~ArrayBuffer()
{
    delete[] buffer_;
}


int uv::ArrayBuffer::append(const char* data, uint64_t size)
{
    SizeInfo info;
    usableSizeInfo(info);

    if (info.size < size)
    {
        //缓存不够
        return -1;
    }
    if (info.part1 >= size)
    {
        std::copy(data, data + size, buffer_ + writeIndex_);
    }
    else
    {
        std::copy(data, data + info.part1, buffer_ + writeIndex_);
        std::copy(data + info.part1, data + size, buffer_);
    }
    addWriteIndex(size);
    return 0;

}

int uv::ArrayBuffer::readBufferN(std::string& data, uint64_t N)
{
    SizeInfo info;
    readSizeInfo(info);
    if (N > readSize())
    {
        return -1;
    }
    int start = (int)data.size();
    data.resize(start + N);
    //string被resize空间，所以操作指针安全
    char* out = const_cast<char*>(data.c_str());
    out += start;
    if (N <= info.part1)
    {
        std::copy(buffer_ + readIndex_, buffer_ + readIndex_ + N, out);
    }
    else
    {
        std::copy(buffer_ + readIndex_, buffer_ + GlobalConfig::CycleBufferSize, out);
        uint64_t remain = N - info.part1;
        std::copy(buffer_, buffer_ + remain, out + info.part1);
    }

    return 0;
}

int uv::ArrayBuffer::clearBufferN(uint64_t N)
{
    if(N>readSize())
    {
        N =readSize();
    }
    addReadIndex(N);
    return 0;
}

int uv::ArrayBuffer::clear()
{
    writeIndex_ = 0;
    readIndex_ = 0;
    return 0;
}

uint64_t uv::ArrayBuffer::usableSize()
{
    uint64_t usable;
    if (writeIndex_ < readIndex_)
    {
        usable = readIndex_ - writeIndex_ - 1;
    }
    else
    {
        usable = GlobalConfig::CycleBufferSize + readIndex_- writeIndex_-1;
    }
    return usable;
}

void uv::ArrayBuffer::usableSizeInfo(SizeInfo& info)
{
    if (writeIndex_ < readIndex_)
    {
        info.part1 = readIndex_ - writeIndex_ - 1;
        info.part2 = 0;
    }
    else
    {
        bool readIsZore = (0 == readIndex_);
        info.part1 = readIsZore ? GlobalConfig::CycleBufferSize - writeIndex_-1: GlobalConfig::CycleBufferSize - writeIndex_;
        info.part2 = readIsZore ? 0 : readIndex_ - 1;
    }
    info.size = info.part1 + info.part2;
}

uint64_t uv::ArrayBuffer::readSize()
{
    SizeInfo info;
    readSizeInfo(info);
    return info.size;
}

void uv::ArrayBuffer::readSizeInfo(SizeInfo& info)
{
    if (writeIndex_ >= readIndex_)
    {
        info.part1 = writeIndex_ - readIndex_;
        info.part2 = 0;
    }
    else
    {
        info.part1 = GlobalConfig::CycleBufferSize - readIndex_;
        info.part2 = writeIndex_;
    }
    info.size = info.part1 + info.part2;
}

int uv::ArrayBuffer::addWriteIndex(uint64_t size)
{
    if (size > GlobalConfig::CycleBufferSize)
        return -1;
    writeIndex_ += size;
    if (writeIndex_ >= GlobalConfig::CycleBufferSize)
        writeIndex_ -= GlobalConfig::CycleBufferSize;
    return 0;
}

int uv::ArrayBuffer::addReadIndex(uint64_t size)
{
    if (size > GlobalConfig::CycleBufferSize)
        return -1;
    readIndex_ += size;
    if (readIndex_ >= GlobalConfig::CycleBufferSize)
        readIndex_ -= GlobalConfig::CycleBufferSize;
    return 0;
}
