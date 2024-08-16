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

namespace logger
{
    void info(std::string s)
    {
        std::cout << CYAN << s << RESET << std::endl;
    }
    void info(const char *s)
    {
        std::cout << CYAN << s << RESET << std::endl;
    }
    void success(std::string s)
    {
        std::cout << GREEN << s << RESET << std::endl;
        // printf("%s%s%s", GREEN, s, RESET_NEWLINE);
    }

    void success(const char *s)
    {
        std::cout << GREEN << s << RESET << std::endl;
    }
    void error(std::string s)
    {
        std::cout << RED << s << RESET << std::endl;
    }

    void error(const char *s)
    {
        std::cout << RED << s << RESET << std::endl;
    }
    void warn(std::string s)
    {
        std::cout << YELLOW << s << RESET << std::endl;
    }
    void warn(const char *s)
    {
        std::cout << YELLOW << s << RESET << std::endl;
    }
}