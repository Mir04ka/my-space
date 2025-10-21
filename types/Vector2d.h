#pragma once
#include <cmath>

struct Vector2d {
    double x = 0;
    double y = 0;

    Vector2d() = default;
    Vector2d(double x, double y) : x(x), y(y) {}

    Vector2d operator+(const Vector2d &other) const { return {x + other.x, y + other.y}; }
    Vector2d operator-(const Vector2d &other) const { return {x - other.x, y - other.y}; }
    Vector2d operator*(double s) const { return {x * s, y * s}; }
    Vector2d operator*(Vector2d vec) const { return {x * vec.x, y * vec.y}; }
    Vector2d operator/(double s) const { return {x / s, y / s}; }

    Vector2d& operator+=(const Vector2d &other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    double distanceTo(const Vector2d &other) const { return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2)); }
    double length() const { return sqrt(x*x + y*y); }
    Vector2d normalize() const {
        double len = length();
        if (len == 0) return Vector2d(0,0);
        return Vector2d(x / len, y / len);
    }
};

inline Vector2 toVector2(const Vector2d& v) {
    return Vector2{ (float)v.x, (float)v.y };
}
