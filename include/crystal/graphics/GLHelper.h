#include <glad/glad.h>
#include "crystal/core/Logger.h"
#include <string>
#define GL_CALL(x)               \
    {                            \
        x;                       \
        crystal::CheckGLError(); \
    }
namespace crystal
{
    std::string DecodeGLError(int error);
    void CheckGLError();
}

