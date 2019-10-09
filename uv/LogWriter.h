/*
Copyright © 2017-2019, orcaer@yeah.net  All rights reserved.

Author: orcaer@yeah.net

Last modified: 2019-10-9

Description: https://github.com/wlgq2/uv-cpp
*/

#ifndef     UV_LOG_INTERFACE_H
#define     UV_LOG_INTERFACE_H

#include  <string>
#include  <functional>
#include  <vector>

#define   USED_STD_OUT     1

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
        Fatal,
        LevelSize
    };
    static LogWriter* Instance();
    static void ToHex(std::string& message, const char* data, unsigned int size);
    static void ToHex(std::string& message, std::string& data);

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
    const std::string& getLevelName(int level);

private:
    LogWriter();

    WriteLogCallback callback_;
    int level_;
    std::vector<std::string> levelStr_;
    std::string nullLevel_;
};
}
#endif // !  UV_LOG_INTERFACE_H

