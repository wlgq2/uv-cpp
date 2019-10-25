/*
   Copyright © 2017-2019, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net

   Last modified: 2019-10-25

   Description: https://github.com/wlgq2/uv-cpp
*/

#include "GlobalConfig.h"

using namespace uv;

//默认不使用buffer
GlobalConfig::BufferMode GlobalConfig::BufferModeStatus = GlobalConfig::BufferMode::NoBuffer;

//默认循环buffer容量32Kb。
uint64_t   GlobalConfig::GlobalConfig::CycleBufferSize = 1024 << 5;
