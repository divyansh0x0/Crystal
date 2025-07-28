#pragma once
#define GL_CALL(x)                                          \
    do                                                      \
    {                                                       \
        x;                                                  \
        platform::gl::CheckGLError(__FILE__, __LINE__, #x); \
    } while (0)

namespace platform::gl
{
    void CheckGLError(const char* file, int line, const char* expr);
}
