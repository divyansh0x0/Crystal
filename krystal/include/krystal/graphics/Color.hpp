#pragma once
#include <inttypes.h>
#include <string>

namespace ktl
{
    struct RGBA
    {
            float r = 0.0; // red
            float g = 0.0; // green
            float b = 0.0; // blue
            float a = 1.0; // alpha

            operator std::string() const
            {
                return "rgba( " + std::to_string(r) + "," + std::to_string(g) + "," + std::to_string(b) + ","
                       + std::to_string(a) + ")";
            }
    };

    struct HSV
    {
            uint8_t h = 0;
            uint8_t s = 0;
            uint8_t v = 0;
    };

    class Color
    {
        private:
            RGBA rgba;

        public:

            Color(uint8_t r, uint8_t g, uint8_t b, float a);
            // const HSV& getHSV();
            const RGBA& getRGBA() const;

            operator std::string() { return rgba; }
    };
} // namespace ktl