#pragma once
#include "crystal/geometry/Matrix.h"
#include <cmath>

namespace crystal::geometry
{
/**
 * @class Vector
 * @brief A class representing a 2D vector for linear algebra operations.
 */
class Vector3
{
    private:
        float x;
        float y;
        float z;

    public:
        Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
        Vector3(const Vector3 &other) : x(other.x), y(other.y), z(other.z) {}

        Vector3(const std::vector<float> &arr) : x(arr[0]), y(arr[1]), z(arr[2])
        {
        }
        Vector3(const float arr[3]) : x(arr[0]), y(arr[1]), z(arr[2]) {};
        Vector3() : x(0), y(0), z(0) {}

        Vector3 operator+(const Vector3 &other) const;
        Vector3 &operator+=(const Vector3 &other);
        Vector3 operator-(const Vector3 &other) const;
        Vector3 &operator-=(const Vector3 &other);
        Vector3 operator*(const float scalar) const;
        Vector3 &operator*=(const float scalar);
        Vector3 operator*(const Vector3 &other) const;
        Vector3 &operator*=(const Vector3 &other);
        Vector3 operator/(const float scalar) const;
        Vector3 &operator/=(const float scalar);
        Vector3 &operator=(const Vector3 &other);
        float operator[](const size_t index) const;
        bool operator==(const Vector3 &other) const;
        bool operator!=(const Vector3 &other) const;

        [[nodiscard]] float dot(const Vector3 &other) const;
        [[nodiscard]] Vector3 cross(const Vector3 &other) const;
        [[nodiscard]] float magnitude() const;
        [[nodiscard]] float squaredMagnitude() const;

        [[nodiscard]] constexpr float squaredMagnitude()
        {
            return x * x + y * y + z * z;
        };
        [[nodiscard]] Vector3 normalize() const;
        [[nodiscard]] float getAngle(const Vector3 &other) const;
        [[nodiscard]] float getDistance(const Vector3 &other) const;
        [[nodiscard]] float getDistanceSquared(const Vector3 &other) const;

        float getX() const { return x; };
        float getY() const { return y; };
        float getZ() const { return z; };
        Matrix getColumnMatrix() const;
        std::string toString() const;
};

static const Vector3 zero   = Vector3(0, 0, 0);
static const Vector3 unit_x = Vector3(1, 0, 0);
static const Vector3 unit_y = Vector3(0, 1, 0);
static const Vector3 unit_z = Vector3(0, 0, 1);
} // namespace crystal::geometry
