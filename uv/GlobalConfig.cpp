/*
   Copyright © 2017-2019, orcaer@yeah.net  All rights reserved.

   Author: orcaer@yeah.net

   Last modified: 2019-10-25

   Description: https://github.com/wlgq2/uv-cpp
*/

#include <functional>

#include "include/GlobalConfig.h"
#include "include/Packet.h"

using namespace uv;
using namespace std;
//默认不使用buffer
GlobalConfig::BufferMode GlobalConfig::BufferModeStatus = GlobalConfig::BufferMode::NoBuffer;

//默认循环buffer容量32Kb。
uint64_t   GlobalConfig::CycleBufferSize = 1024 << 5;

//默认包解析函数
ReadBufferStringFunc GlobalConfig::ReadBufferString = nullptr;
ReadBufferPacketFunc GlobalConfig::ReadBufferPacket = std::bind(&Packet::readFromBuffer, placeholders::_1, placeholders::_2);;
ReadBufferVoidFunc GlobalConfig::ReadBufferVoid = nullptr;
