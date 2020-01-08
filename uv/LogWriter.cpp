/*
Copyright © 2017-2019, orcaer@yeah.net  All rights reserved.

Author: orcaer@yeah.net

Last modified: 2019-10-9

Description: https://github.com/wlgq2/uv-cpp
*/

#include "include/LogWriter.h"

#include <iostream>


using namespace uv;

LogWriter* LogWriter::Instance()
{
    static LogWriter single;
    return &single;
}

void uv::LogWriter::registerInterface(WriteLogCallback callback)
{
    callback_ = callback;
}

void uv::LogWriter::ToHex(std::string& message, const char* data, unsigned int size)
{
    for (unsigned int i = 0; i < size; i++)
    {
        char buf[8];
        std::sprintf(buf, " 0x%x ", (unsigned char)data[i]);
        message.append(buf);
    }
}

void uv::LogWriter::ToHex(std::string& message, std::string& data)
{
    ToHex(message, data.c_str(), (unsigned)(data.size()));
}

void uv::LogWriter::write(Level level, const std::string& data)
{
    if ((level <= Error) && (level >= level_) && (level >= Debug))
    {
        if (callback_)
        {
            callback_(level, data);
        }
        else
        {
#if    USED_STD_OUT
            std::cout << getLevelName(level) << " :" << data << std::endl;
#endif
        }
    }
}

void uv::LogWriter::write(Level level, const std::string&& data)
{
    write(level, data);
}

void uv::LogWriter::fatal(const std::string& data)
{
    write(Level::Fatal, data);
}

void uv::LogWriter::fatal(const std::string&& data)
{
    write(Level::Fatal, data);
}

void uv::LogWriter::warn(const std::string& data)
{
    write(Level::Warn, data);
}

void uv::LogWriter::warn(const std::string&& data)
{
    write(Level::Warn, data);
}

void uv::LogWriter::error(const std::string& data)
{
    write(Level::Error, data);
}

void uv::LogWriter::error(const std::string&& data)
{
    write(Level::Error, data);
}

void uv::LogWriter::info(const std::string& data)
{
    write(Level::Info, data);
}

void uv::LogWriter::info(const std::string&& data)
{
    write(Level::Info, data);
}

void uv::LogWriter::debug(const std::string& data)
{
    write(Level::Debug, data);
}

void uv::LogWriter::debug(const std::string&& data)
{
    write(Level::Debug, data);
}

void uv::LogWriter::setLevel(int level)
{
    level_ = level;
}

int uv::LogWriter::getLevel()
{
    return level_;
}

const std::string& uv::LogWriter::getLevelName(int level)
{
    if (level >= 0 && level <=static_cast<int>(levelStr_.size()))
    {
        return levelStr_[level];
    }
    return nullLevel_;
}

LogWriter::LogWriter()
    :callback_(nullptr),
    level_(0)
{
    levelStr_.resize(Level::LevelSize);
    levelStr_[Level::Debug] = "Debug";
    levelStr_[Level::Info] = "Info";
    levelStr_[Level::Warn] = "Warn";
    levelStr_[Level::Error] = "Error";
    levelStr_[Level::Fatal] = "Fatal";

    nullLevel_ = "NullLevel";
}