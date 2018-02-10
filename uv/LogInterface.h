/*
Copyright 2017, object_he@yeah.net  All rights reserved.

Author: object_he@yeah.net

Last modified: 2017-12-5

Description:
*/

#ifndef     UV_LOG_INTERFACE_H
#define     UV_LOG_INTERFACE_H

#include <string>
#include <functional>

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
    using OutMessageType = std::function<void(const std::string&)>;
    enum Delel{
        Debug = 0,
        Info,
        Warn,
        Error
    };
    static Log* Instance()
    {
        static Log single;
        return &single;
    }
    void registerInterface(LogInterface* handle)
    {
        handle_ = handle;
        funcs_[Debug] = std::bind(&LogInterface::debug, handle_, std::placeholders::_1);
        funcs_[Info] = std::bind(&LogInterface::info, handle_, std::placeholders::_1);
        funcs_[Warn] = std::bind(&LogInterface::warn, handle_, std::placeholders::_1);
        funcs_[Error] = std::bind(&LogInterface::error, handle_, std::placeholders::_1);
    }
    void write(int level,std::string& data)
    {
        if ((handle_) &&(level<= Error) && (level >= Debug))
        {
            funcs_[level](data);
        }
    }
    void write(int level, std::string&& data)
    {
        if ((handle_) && (level <= Error))
        {
            funcs_[level](data);
        }
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

    static void toHex(std::string& message,const char* data,unsigned int size)
    {
        for (unsigned int i = 0; i < size; i++)
        {
            char buf[8];
            std::sprintf(buf, " 0x%x ", (unsigned char)data[i]);
            message += buf;
        }
    }
private:
    Log():handle_(nullptr)
    {
    }

    LogInterface* handle_;
    OutMessageType funcs_[Error + 1];
};
}
#endif // !  UV_LOG_INTERFACE_H

