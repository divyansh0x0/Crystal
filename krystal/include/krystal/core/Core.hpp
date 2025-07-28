#pragma once
#include <memory>


#ifndef NDEBUG

#define CRYSTAL_ASSERT(expr, message)                                                                          \
    do                                                                                                         \
    {                                                                                                          \
        if (!(expr))                                                                                           \
        {                                                                                                      \
            std::fprintf(stderr, "Assertion failed: (%s)\nFile: %s\nLine: %d\nMessage: %s\n", #expr, __FILE__, \
                         __LINE__, message);                                                                   \
            std::abort();                                                                                      \
        }                                                                                                      \
    } while (0)

#else

#define CRYSTAL_ASSERT(expr, message) ((void) 0)

#endif

#ifndef CRYSTAL_BUILD_DLL
    #define CRYSTAL_API __declspec(dllexport)
#else
    #define CRYSTAL_API __declspec(dllimport)
#endif


namespace ktl
{

     template <typename T>
     using Shared = std::shared_ptr<T>;


    template <typename T>
    using Owned = std::unique_ptr<T>;
} // namespace ktl