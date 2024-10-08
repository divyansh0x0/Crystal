#include "crystal/geometry/Vector3.h"
#include "crystal/core/Logger.h"
#include <cmath>
static float FastInverseSqrt(float num)
{
    union
    {
            float f;
            long  i;
    } conv;

    const float threehalfs = 1.5F;

    float x2 = num * 0.5F;
    conv.f   = num;
    conv.i   = 0x5f3759df - (conv.i >> 1);
    conv.f   = conv.f * (threehalfs - (x2 * conv.f * conv.f));

    return conv.f;
}
namespace crystal::geometry
{

Vector3 Vector3::operator+(const Vector3& other) const
{
    return Vector3(x + other.x, y + other.y, z + other.z);
}
Vector3& Vector3::operator+=(const Vector3& other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Vector3 Vector3::operator-(const Vector3& other) const
{
    return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3& Vector3::operator-=(const Vector3& other)
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
Vector3& Vector3::operator*=(const float scalar)
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
            logger::Error("Index out of range");
            return 0;
    }
}

// cross product
Vector3 Vector3::operator*(const Vector3& other) const
{
    return Vector3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
}
Vector3& Vector3::operator*=(const Vector3& other)
{
    *this = *this * other;
    return *this;
}

Vector3 Vector3::operator/(const float scalar) const
{
    return Vector3(x / scalar, y / scalar, z / scalar);
}
Vector3& Vector3::operator/=(const float scalar)
{
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
}

// copy

Vector3& Vector3::operator=(const Vector3& other)
{
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
}
// equality

bool Vector3::operator==(const Vector3& other) const
{
    return x == other.x && y == other.y && z == other.z;
}
bool Vector3::operator!=(const Vector3& other) const
{
    return !(*this == other);
}

float Vector3::dot(const Vector3& other) const
{
    return x * other.x + y * other.y + z * other.z;
}
Vector3 Vector3::cross(const Vector3& other) const
{
    return *this * other;
}

float Vector3::magnitude() const
{
    return std::sqrt(x * x + y * y + z * z);
}

float Vector3::squaredMagnitude() const
{
    return x * x + y * y + z * z;
}

Vector3 Vector3::normalize() const
{
    return *this * FastInverseSqrt(x * x + y * y + z * z);
}

float Vector3::getAngle(const Vector3& other) const
{
    return std::acos(dot(other) / (magnitude() * other.magnitude()));
}
float Vector3::getDistance(const Vector3& other) const
{
    return (other - *this).magnitude();
}

float Vector3::getDistanceSquared(const Vector3& other) const
{
    return (other - *this).squaredMagnitude();
}

Matrix Vector3::getColumnMatrix()
{


    return Matrix({{x}, {y}, {z}});
}

std::string Vector3::toString() const
{
    return "(" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + ")";
}

} // namespace crystal::geometry