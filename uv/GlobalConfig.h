/*
   Copyright © 2017-2019, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net

   Last modified: 2019-10-25

   Description: https://github.com/wlgq2/uv-cpp
*/

#ifndef UV_GLOBAL_CONFIG_H
#define UV_GLOBAL_CONFIG_H

#include <string>

namespace uv
{
class GlobalConfig
{
public:
    enum BufferMode
    {
        NoBuffer,
        CycleBuffer,
        ListBuffer
    };
    static BufferMode BufferModeStatus;
    static uint64_t   CycleBufferSize;
};
}
#endif
