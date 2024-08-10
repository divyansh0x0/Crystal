#include "core/geometry/Vector3.h"
#include<cmath>
#include<vector>
#include<stdexcept>
using namespace crystal::geometry;

// Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

// Vector3::Vector3(const Vector3 &other) : x(other.x), y(other.y), z(other.z) {}

// Vector3::Vector3(const std::vector<float> &arr) : x(arr[0]), y(arr[1]), z(arr[2]) {}

Vector3 Vector3::operator+(const Vector3 &other) const{
    return Vector3(x + other.x, y + other.y, z + other.z);
}
Vector3& Vector3::operator+=(const Vector3 &other){
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Vector3 Vector3::operator-(const Vector3 &other) const{
    return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3& Vector3::operator-=(const Vector3 &other){
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}
Vector3 Vector3::operator*(const float scalar) const{
    return Vector3(x * scalar, y * scalar, z * scalar);
}
Vector3& Vector3::operator*=(const float scalar){
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}   
//array access

float Vector3::operator[](const size_t index) const{
    switch(index){
        case 0: return x;
        case 1: return y;
        case 2: return z;
        default: throw std::range_error("Index out of range");
    }
}

//cross product
Vector3 Vector3::operator*(const Vector3 &other) const{
    return Vector3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
}
Vector3& Vector3::operator*=(const Vector3 &other){
    *this = *this * other;
    return *this;
}



Vector3 Vector3::operator/(const float scalar) const{
    return Vector3(x / scalar, y / scalar, z / scalar);
}
Vector3& Vector3::operator/=(const float scalar){
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
}


//copy

Vector3& Vector3::operator=(const Vector3 &other) {
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
}
//equality

bool Vector3::operator==(const Vector3 &other) const{
    return x == other.x && y == other.y && z == other.z;
}
bool Vector3::operator!=(const Vector3 &other) const{
    return !(*this == other);
}




float Vector3::dot(const Vector3 &other) const{
    return x * other.x + y * other.y + z * other.z;
}
Vector3 Vector3::cross(const Vector3 &other) const{
    return *this * other;
}

float Vector3::magnitude() const{
    if (!cached_magnitude.has_value()) {
             cached_magnitude =std::sqrt(x * x + y * y + z * z);

    }
    return cached_magnitude.value();
}

float Vector3::squaredMagnitude() const{
    float mag = magnitude();
    return mag * mag;
}


Vector3 Vector3::normalize() const{
    return *this / magnitude();
}

float Vector3::getAngle(const Vector3 &other) const{
    return std::acos(dot(other) / (magnitude() * other.magnitude()));
}
float Vector3::getDistance(const Vector3 &other) const{
    return (other - *this).magnitude();
}

float Vector3::getDistanceSquared(const Vector3 &other) const{
    return (other - *this).squaredMagnitude();
}

Matrix Vector3::getColumnMatrix() const{
    std::vector<std::vector<float>> arr = {{x, {y}, {z}}};
    return Matrix( arr);
}

std::string Vector3::toString() const{
    return "("+std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + ")";
}


