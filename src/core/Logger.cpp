#include "crystal/core/Logger.h"
#include <iostream>
// #include <string.h>
// #include <iostream>
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define RESET "\x1b[0m"

namespace logger {
    void Info(const std::string &type, const std::string &s) {
        std::cout << CYAN << "[" << type << "] " << s << RESET << std::endl;
    }

    void Info(const std::string &s) { Info("MESSAGE", s); }

    void Error(const std::string &type, const std::string &s) {
        std::cout << CYAN << "[" << type << "] " << s << RESET << std::endl;
    }

    void Error(const std::string &s) { Error("ERROR", s); }

    void Warn(const std::string &type, const std::string &s) {
        std::cout << CYAN << "[" << type << "] " << s << RESET << std::endl;
    }

    void Warn(const std::string &s) { Warn("WARN", s); }

    void Success(const std::string &type, const std::string &s) {
        std::cout << CYAN << "[" << type << "] " << s << RESET << std::endl;
    }

    void Success(const std::string &s) { Success("SUCCESS", s); }
} // namespace logger