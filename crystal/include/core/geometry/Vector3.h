#pragma once
#include "core/geometry/Matrix.h"
#include<optional>
namespace crystal::geometry
{
    /**
     * @class Vector
     * @brief A class representing a 2D vector for linear algebra operations.
     */
    class Vector3
    {
    private:
        double x;
        double y;
        double z;
        mutable std::optional<double> cached_magnitude;
    public:

        Vector3(double x, double y, double z) : x(x), y(y), z(z) {}
        Vector3(const Vector3 &other) : x(other.x), y(other.y), z(other.z) {}
        Vector3(const std::vector<double> &arr) : x(arr[0]), y(arr[1]), z(arr[2]) {}
        Vector3() : x(0), y(0), z(0) {}

        Vector3 operator+(const Vector3 &other) const;
        Vector3 &operator+=(const Vector3 &other);
        Vector3 operator-(const Vector3 &other) const;
        Vector3 &operator-=(const Vector3 &other);
        Vector3 operator*(const double scalar) const;
        Vector3 &operator*=(const double scalar);
        Vector3 operator*(const Vector3 &other) const;
        Vector3 &operator*=(const Vector3 &other);
        Vector3 operator/(const double scalar) const;
        Vector3 &operator/=(const double scalar);
        Vector3 &operator=(const Vector3 &other);
        double operator[](const size_t index) const;
        bool operator==(const Vector3 &other) const;
        bool operator!=(const Vector3 &other) const;

        double dot(const Vector3 &other) const;
        Vector3 cross(const Vector3 &other) const;

        double magnitude() const;
        double squaredMagnitude() const;
        Vector3 normalize() const;
        double getAngle(const Vector3 &other) const;
        double getDistance(const Vector3 &other) const;
        double getDistanceSquared(const Vector3 &other) const;


        double getX() const {return x;};
        double getY() const {return y;};
        double getZ() const {return z;};
        Matrix getColumnMatrix() const;
        std::string toString() const;
    };

    static const Vector3 ZERO = Vector3(0, 0, 0);
    static const Vector3 UNIT_X = Vector3(1, 0, 0);
    static const Vector3 UNIT_Y = Vector3(0, 1, 0);
    static const Vector3 UNIT_Z = Vector3(0, 0, 1);
}
