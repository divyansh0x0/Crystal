#include <log.h>
#include <stdio.h>
#include <stdarg.h>
// #include <string.h>
// #include <iostream>
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define RESET_NEWLINE "\x1b[0m\n"

// Implementation of variable arguments using variadic templates.
// using namespace std;

void log::info(const char *s)
{
    printf("%s%s%s", CYAN, s, RESET_NEWLINE);
}

void log::success(const char *s)
{
    printf("%s%s%s", GREEN, s, RESET_NEWLINE);
}

void log::error(const char *s)
{
    printf("%s%s%s", RED, s, RESET_NEWLINE);
}

void log::warn(const char *s)
{
    printf("%s%s%s", YELLOW, s, RESET_NEWLINE);
}
