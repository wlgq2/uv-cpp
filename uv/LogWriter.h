/*
Copyright 2017, orcaer@yeah.net  All rights reserved.

Author: orcaer@yeah.net

Last modified: 2019-8-4

Description: https://github.com/wlgq2/libuv_cpp11
*/

#ifndef     UV_LOG_INTERFACE_H
#define     UV_LOG_INTERFACE_H

#include <string>
#include <functional>

namespace uv
{

class LogWriter
{
public:
    using WriteLogCallback = std::function<void(int level,const std::string&)>;

    enum Level{
        Debug = 0,
        Info,
        Warn,
        Error,
        Fatal
    };
    static LogWriter* Instance();
    static void ToHex(std::string& message, const char* data, unsigned int size);

public:
    void registerInterface(WriteLogCallback callback);

    void write(Level level, const std::string& data);
    void write(Level level, const std::string&& data);

    void fatal(const std::string& data);
    void fatal(const std::string&& data);
    void warn(const std::string& data);
    void warn(const std::string&& data);
    void error(const std::string& data);
    void error(const std::string&& data);
    void info(const std::string& data);
    void info(const std::string&& data);
    void debug(const std::string& data);
    void debug(const std::string&& data);

    void setLevel(int level);
    int getLevel();

private:
    LogWriter();

    WriteLogCallback callback_;
    int level_;
};
}
#endif // !  UV_LOG_INTERFACE_H

