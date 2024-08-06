#pragma once

#include <string>

namespace logger
{
    void info(const char * s);
    void info(std::string s);
    void warn(const char * s);
    void warn(std::string s);
    void error(const char * s);
    void error(std::string s);
    void success(const char * s);
    void success(std::string s);

}
