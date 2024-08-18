#pragma once

#include <string>

namespace logger
{
    enum class LogType{
        INFO = 0,
        WARN = 1,
        ERROR = 2,
        SUCCESS = 3,
        DESTRUCTION = 4,
        CONSTRUCTION = 5,
        MATH=6,
        GRAPHICS=7,
        PHYSICS=8,
        AUDIO=9,
        USER=10,
        VULKAN=11,
        OPENGL=12,
        DIRECTX=13,
        SHADER=14,
        RESOURCE=15,
        MESSAGE=16,

    };
    void Info(const std::string& s);
    void Info(LogType type,const std::string& s);

    void Warn(const std::string& s);
    void Warn(LogType type,const std::string& s);

    void Error(const std::string& s);
    void Error(LogType type, const std::string& s);

    void Success(const std::string& s);
    void Success(LogType type, const std::string& s);

}
