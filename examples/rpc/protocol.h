/*
   Copyright © 2017-2019, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net

   Last modified: 2019-9-20

   Description: https://github.com/wlgq2/uv-cpp
*/


#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <vector>

struct Req
{
    std::vector<int32_t> params;

    int size()
    {
        return (int)params.size() * 4;
    }
    int pack(char* data, int size)
    {
        if (size < this->size())
        {
            return -1;
        }
        
        for (int32_t param : params)
        {
            std::copy((char*)(&param), (char*)(&param + 1), data);
            data += sizeof(param);
        }
        return 0;
    }
    int unpack(const char* data, int size)
    {
        if (size % 4 != 0)
        {
            return -1;
        }

        params.clear();
        for (auto i = 0; i < size; i+=4)
        {
            int32_t num;
            num = *((int32_t*)(data + i));
            params.push_back(num);
        }
        return 0;
    }
};

struct Resp
{
    int64_t param;
    int size()
    {
        return sizeof(int64_t);
    }
    int pack(char* data, int size)
    {
        if (size < this->size())
        {
            return -1;
        }
        std::copy((char*)(&param), (char*)(&param + 1), data);
        return 0;
    }

    int unpack(const char* data, int size)
    {
        if (size < this->size())
        {
            return -1;
        }
        param = *((int64_t*)data);
        return 0;
    }
};

#endif