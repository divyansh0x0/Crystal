#pragma once
#include <inttypes.h>
namespace crystal
{
struct RGBA
{
        uint8_t r; // red
        uint8_t g; // green
        uint8_t b; // blue
        uint8_t a; // alpha
};
struct HSV
{
        uint8_t h;
        uint8_t s;
        uint8_t v;
};
class Color
{
    private:
        RGBA rgba;

    public:
        Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
        Color(uint8_t r, uint8_t g, uint8_t b) : Color(r, g, b, 255) {};
        // const HSV& getHSV();
        const RGBA &getRGBA();
};
} // namespace crystal