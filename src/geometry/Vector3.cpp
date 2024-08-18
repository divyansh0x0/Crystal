#include "crystal/geometry/Vector3.h"
#include <cmath>
#include <vector>
#include <stdexcept>
static float FastInverseSqrt(float x) {
    long i;
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = x * 0.5F;
    y = x;
    i = *(long*)&y;
    i = 0x5f3759df - (i >> 1);
    y = *(float*)&i;
    y = y * (threehalfs - (x2 * y * y));

    return y;
}
namespace crystal::geometry
{

    Vector3 Vector3::operator+(const Vector3 &other) const
    {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }
    Vector3 &Vector3::operator+=(const Vector3 &other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    Vector3 Vector3::operator-(const Vector3 &other) const
    {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    Vector3 &Vector3::operator-=(const Vector3 &other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }
    Vector3 Vector3::operator*(const float scalar) const
    {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }
    Vector3 &Vector3::operator*=(const float scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }
    // array access

    float Vector3::operator[](const size_t index) const
    {
        switch (index)
        {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        default:
            throw std::range_error("Index out of range");
        }
    }

    // cross product
    Vector3 Vector3::operator*(const Vector3 &other) const
    {
        return Vector3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
    }
    Vector3 &Vector3::operator*=(const Vector3 &other)
    {
        *this = *this * other;
        return *this;
    }

    Vector3 Vector3::operator/(const float scalar) const
    {
        return Vector3(x / scalar, y / scalar, z / scalar);
    }
    Vector3 &Vector3::operator/=(const float scalar)
    {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }

    // copy

    Vector3 &Vector3::operator=(const Vector3 &other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }
    // equality

    bool Vector3::operator==(const Vector3 &other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }
    bool Vector3::operator!=(const Vector3 &other) const
    {
        return !(*this == other);
    }

    float Vector3::dot(const Vector3 &other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }
    Vector3 Vector3::cross(const Vector3 &other) const
    {
        return *this * other;
    }

    float Vector3::magnitude() const
    {
        return  std::sqrt(x * x + y * y + z * z);
    }

    float Vector3::squaredMagnitude() const
    {
        return x*x + y*y + z*z;
    }

    Vector3 Vector3::normalize() const
    {
        return *this * FastInverseSqrt(x * x + y * y + z * z);
    }

    float Vector3::getAngle(const Vector3 &other) const
    {
        return std::acos(dot(other) / (magnitude() * other.magnitude()));
    }
    float Vector3::getDistance(const Vector3 &other) const
    {
        return (other - *this).magnitude();
    }

    float Vector3::getDistanceSquared(const Vector3 &other) const
    {
        return (other - *this).squaredMagnitude();
    }

    Matrix Vector3::getColumnMatrix() const
    {
        std::vector<std::vector<float>> arr = {{x, {y}, {z}}};
        return Matrix(arr);
    }

    std::string Vector3::toString() const
    {
        return "(" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + ")";
    }

}