/*
    Copyright 2017, orcaer@yeah.net  All rights reserved.

    Author: orcaer@yeah.net

    Last modified: 2018-4-18

    Description: https://github.com/wlgq2/libuv_cpp11
*/


#ifndef LOG_DEMO_H
#define LOG_DEMO_H

#include <uv/LogInterface.h>
#include <iostream>

//log interface instructions, can be bound to your log libary.
//log接口用法，可绑定到实际的log库。
class  LogDemo : public uv::LogInterface
{
public:
    LogDemo()
    {
        
    }
    void warn(const std::string& data) override
    {
        std::cout << "warn :" << data << std::endl;
    }
    virtual void error(const std::string& data) override
    {
        std::cout << "error :" << data << std::endl;
    }
    virtual void info(const std::string& data) override
    {
        std::cout << "info :" << data << std::endl;
    }
    virtual void debug(const std::string& data) override
    {
        std::cout << "debug :" << data << std::endl;
    }

};

#endif
