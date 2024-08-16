#include <glad/glad.h>
#include "crystal/core/Logger.h"
#include <string>
#define GL_CALL(x)                                                                                             \
    {                                                                                                          \
        x;                                                                                                     \
        int error = glGetError();                                                                              \
        if (error != GL_NO_ERROR)                                                                              \
            logger::error(crystal::DecodeGLError(error) + " at " + __FILE__ + ":" + std::to_string(__LINE__)); \
    }
namespace crystal
{
    std::string DecodeGLError(int error);
}
