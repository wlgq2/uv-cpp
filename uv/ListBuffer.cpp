/*
Copyright © 2017-2019, orcaer@yeah.net  All rights reserved.

Author: orcaer@yeah.net

Last modified: 2018-10-24

Description: https://github.com/wlgq2/uv-cpp
*/

#include "include/ListBuffer.h"


#include <iostream>
using namespace uv;
using namespace std;

ListBuffer::ListBuffer()
{

}

ListBuffer::~ListBuffer()
{

}

int ListBuffer::append(const char* data, uint64_t size)
{
    for (uint64_t i = 0; i < size; i++)
        buffer_.push_back(data[i]);
    return 0;
}


int uv::ListBuffer::readBufferN(std::string& data, uint64_t N)
{
    if (N > (uint64_t)buffer_.size())
        return -1;
    auto it = buffer_.begin();
    for (uint64_t i = 0; i < N; i++)
    {
        data.push_back(*it);
        it++;
    }
    return 0;
}

uint64_t uv::ListBuffer::readSize()
{
    return (uint64_t)buffer_.size();
}

int uv::ListBuffer::clearBufferN(uint64_t N)
{
    for (uint64_t i = 0; i < N; i++)
    {
        if (buffer_.empty())
            break;
        buffer_.pop_front();
    }
    return 0;
}

int uv::ListBuffer::clear()
{
    buffer_.clear();
    return 0;
}
