/*
Copyright 2017, orcaer@yeah.net  All rights reserved.

Author: orcaer@yeah.net

Last modified: 2019-8-4

Description: https://github.com/wlgq2/uv-cpp
*/

#include "LogWriter.h"

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
        message += buf;
    }
}

void uv::LogWriter::write(Level level, const std::string& data)
{
    if ((callback_) && (level <= Error) && (level >= Debug))
    {
        callback_(level, data);
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

LogWriter::LogWriter()
    :callback_(nullptr),
    level_(0)
{
}