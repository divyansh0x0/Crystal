#include "crystal/core/Color.h"
namespace crystal
{
Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    rgba.r = r;
    rgba.g = g;
    rgba.b = b;
    rgba.a = a;
}
const RGBA &crystal::Color::getRGBA()
{
    return rgba;
}
} // namespace crystal