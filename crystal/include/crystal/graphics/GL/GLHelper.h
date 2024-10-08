#include <string>
#define GL_CALL(x)                                                         \
    {                                                                      \
        x;                                                                 \
        int error = glGetError();                                          \
        if (error != 0)                                                    \
            logger::Error("OpenGL", crystal::DecodeGLError(error) + " at " \
                                        + __FILE__ + ":"                   \
                                        + std::to_string(__LINE__));       \
    }
namespace crystal
{
std::string DecodeGLError(int error);
}
