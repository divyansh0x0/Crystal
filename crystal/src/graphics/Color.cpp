#include "crystal/graphics/Color.hpp"

namespace crystal
{
    Color::Color(uint8_t r, uint8_t g, uint8_t b, float a)
    {
        rgba.r = r/255.0f;
        rgba.g = g/255.0f;
        rgba.b = b/255.0f;
        rgba.a = a;
    }

    const RGBA& crystal::Color::getRGBA () const
    {
        return rgba;
    }
} // namespace crystal