#pragma once

#include <string>

namespace logger
{
    void Info(const std::string& s);
    void Info(const std::string &type,  const std::string &s);

    void Warn(const std::string& s);
    void Warn(const std::string &type, const std::string &s);

    void Error(const std::string& s);
    void Error(const std::string &type, const std::string &s);

    void Success(const std::string& s);
    void Success(const std::string &type, const std::string &s);
}
