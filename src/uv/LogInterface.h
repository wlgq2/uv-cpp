/*
Copyright 2017, object_he@yeah.net  All rights reserved.

Author: object_he@yeah.net

Last modified: 2017-12-5

Description:
*/

#ifndef     UV_LOG_INTERFACE_H
#define     UV_LOG_INTERFACE_H

#include <string>

namespace uv
{

class LogInterface
{
public:
    virtual ~LogInterface(){}

    virtual void warn(const std::string& data) = 0;
    virtual void error(const std::string& data) = 0;
    virtual void info(const std::string& data) = 0;
    virtual void debug(const std::string& data) = 0;
};

class Log
{
public:
    static Log* Instance()
    {
        static Log single;
        return &single;
    }
    void registerInterface(LogInterface* handle)
    {
        handle_ = handle;
    }
    void warn(const std::string& data)
    {
        if (handle_)
            handle_->warn(data);
    }
    void warn(const std::string&& data)
    {
        if (handle_)
            handle_->warn(data);
    }
    void error(const std::string& data)
    {
        if (handle_)
            handle_->error(data);
    }
    void error(const std::string&& data)
    {
        if (handle_)
            handle_->error(data);
    }
    void info(const std::string& data)
    {
        if (handle_)
            handle_->info(data);
    }
    void info(const std::string&& data)
    {
        if (handle_)
            handle_->info(data);
    }
    void debug(const std::string& data)
    {
        if (handle_)
            handle_->debug(data);
    }
    void debug(const std::string&& data)
    {
        if (handle_)
            handle_->debug(data);
    }
    
private:
    Log():handle_(nullptr)
    {
    }

    LogInterface* handle_;
};
}
#endif // !  UV_LOG_INTERFACE_H

