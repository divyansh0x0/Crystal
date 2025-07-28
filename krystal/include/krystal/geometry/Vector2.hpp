#pragma once
#include "krystal/geometry/Vector3.hpp"

namespace ktl::geometry
{

    class Vector2 : public Vector3
    {
        public:
            Vector2() : Vector3(0, 0, 0) {};
            Vector2(const float x, const float y) : Vector3(x, y, 0) {};
            Vector2(const Vector2& other) : Vector3(other[0], other[1], 0) {};
            explicit Vector2(const float arr[2]) : Vector3(arr[0], arr[1], 0) {};
    };
} // namespace ktl::geometry