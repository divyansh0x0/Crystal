#pragma once
#include "core/geometry/Vector3.h"
namespace crystal::geometry{

    class Vector2 : public Vector3{
    public:
        Vector2() : Vector3(0, 0, 0) {};
        Vector2(float x, float y) : Vector3(x, y, 0) {};
        Vector2(const Vector2 &other) : Vector3(other[0], other[1], 0) {};
        Vector2(const std::vector<float> &arr) : Vector3(arr[0],arr[1],0) {};
    };
}