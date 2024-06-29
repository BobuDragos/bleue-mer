
#include <math.h>
#include "engine.h"

namespace MathEngine
{
    Vector3 Vector3::zero = Vector3(0, 0, 0, 1);
    Vector3 Vector3::one = Vector3(1, 1, 1, 1);

    Vector3::Vector3() : Vector3(0, 0, 0, 1) {}
    Vector3::Vector3(double _x, double _y, double _z, double _w) : x(_x), y(_y), z(_z), w(_w) {}

    Vector3& Vector3::operator=(const Vector3& other) {
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }

    Vector3& Vector3::operator+=(const Vector3& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    Vector3& Vector3::operator*=(double scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    Vector3 Vector3::operator*(double scalar) const {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }

    Vector3 Vector3::operator-(const Vector3& other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    Vector3 Vector3::operator+(const Vector3& other) const {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    double Vector3::dot(const Vector3& other) const {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }

    Vector3 Vector3::operator/(double scalar) const {
        return Vector3(x / scalar, y / scalar, z / scalar);
    }


    double Vector3::distance(const Vector3& other) const
    {
        double dx = x - other.x;
        double dy = y - other.y;
        double dz = z - other.z;
        return sqrt(dx * dx + dy * dy + dz * dz);
    }

    Color Color::black = Color(0.0, 0.0, 0.0, 1.0);
    Color Color::white = Color(1.0, 1.0, 1.0, 1.0);
    Color Color::red = Color(1.0, 0.0, 0.0, 1.0);
    Color Color::green = Color(0.0, 1.0, 0.0, 1.0);
    Color Color::blue = Color(0.0, 0.0, 1.0, 1.0);
    Color Color::yellow = Color(1.0, 1.0, 0.0, 1.0);
    Color Color::cyan = Color(0.0, 1.0, 1.0, 1.0);
    Color Color::magenta = Color(1.0, 0.0, 1.0, 1.0);
    Color Color::gray = Color(0.5, 0.5, 0.5, 1.0);
    Color Color::darkGray = Color(0.25, 0.25, 0.25, 1.0);
    Color Color::lightGray = Color(0.75, 0.75, 0.75, 1.0);
    Color Color::darkRed = Color(0.5, 0.0, 0.0, 1.0);
    Color Color::darkGreen = Color(0.0, 0.5, 0.0, 1.0);
    Color Color::darkBlue = Color(0.0, 0.0, 0.5, 1.0);
    Color Color::brown = Color(0.6, 0.3, 0.1, 1.0);
    Color Color::orange = Color(1.0, 0.5, 0.0, 1.0);

    Color::Color() : r(1.0f), g(1.0f), b(1.0f), a(1.0f) {}
    Color::Color(double _value) : Color(_value, _value, _value, 1.0f) {}
    Color::Color(double _r, double _g, double _b) : Color(_r, _g, _b, 1.0f) {}
    Color::Color(double _r, double _g, double _b, double _a) : r(_r), g(_g), b(_b), a(_a) {}

    // Vector3 Random::Vector3() {
    //     return Math::Vector3(static_cast<double>(rand()) / RAND_MAX, static_cast<double>(rand()) / RAND_MAX, static_cast<double>(rand()) / RAND_MAX, 1.0);
    // }

    // Color Random::Color() {
    //     return Math::Color(static_cast<float>(rand()) / RAND_MAX, static_cast<float>(rand()) / RAND_MAX, static_cast<float>(rand()) / RAND_MAX, 1.0);
    // }
}
// using Math::Vector3;
// using Math::Color;




