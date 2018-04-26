/*
Copyright 2017, orcaer@yeah.net  All rights reserved.

Author: orcaer@yeah.net

Last modified: 2018-4-24

Description: https://github.com/wlgq2/libuv_cpp11
*/

#ifndef UV_LIST_BUFFER_H
#define UV_LIST_BUFFER_H


#include <list>

#include "PacketBuffer.h"


//ListBuffer
//---------------------------------------
//  Null  |  Packet   |  Packet   |  Null 
//---------------------------------------
//        ¡ü                      ¡ü
//   read position           write position

//not thread safe.

namespace uv
{

class ListBuffer : public PacketBuffer
{
public:
    ListBuffer();
    ~ListBuffer();
 
    int append(const char* data, int size) override;
    int read(Packet& packet) override;

private:
    std::list<uint8_t> buffer_;

};

}

#endif // AGILNET_NET_BUFFER
