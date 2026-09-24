#pragma once

#include <cmath>

namespace Aurora
{
    namespace Math
    {
        inline constexpr float Pi = 3.14159265358979323846f;

        constexpr float ToRadians(float degrees)
        {
            return degrees * (Pi / 180.0f);
        }

        constexpr float ToDegrees(float radians)
        {
            return radians * (180.0f / Pi);
        }

        constexpr float Lerp(float a, float b, float t)
        {
            return a + (b - a) * t;
        }

        constexpr float Clamp(float v, float lo, float hi)
        {
            return v < lo ? lo : (v > hi ? hi : v);
        }
    }

    struct Vector2
    {

        float x = 0.0f;
        float y = 0.0f;

        constexpr Vector2() = default;
        constexpr Vector2(float px, float py) : x(px), y(py) {}

        static constexpr Vector2 Zero()
        {
            return {0.0f, 0.0f};
        }

        static constexpr Vector2 One()
        {
            return {1.0f, 1.0f};
        }

        static constexpr Vector2 UnitX()
        {
            return {1.0f, 0.0f};
        }

        static constexpr Vector2 UnitY()
        {
            return {0.0f, 1.0f};
        }

        Vector2 operator+(
            const Vector2 &other) const
        {
            return Vector2(
                x + other.x,
                y + other.y);
        }

        Vector2 operator-(
            const Vector2 &other) const
        {
            return Vector2(
                x - other.x,
                y - other.y);
        }

        Vector2 operator*(
            float value) const
        {
            return Vector2(
                x * value,
                y * value);
        }

        constexpr Vector2 &operator+=(Vector2 o)
        {
            x += o.x;
            y += o.y;
            return *this;
        }

        constexpr Vector2 &operator-=(Vector2 o)
        {
            x -= o.x;
            y -= o.y;
            return *this;
        }

        constexpr Vector2 &operator*=(float s)
        {
            x *= s;
            y *= s;
            return *this;
        }

        constexpr Vector2 &operator/=(float s)
        {
            x /= s;
            y /= s;
            return *this;
        }

        constexpr bool operator==(const Vector2 &) const = default;

        constexpr float Dot(Vector2 o) const
        {
            return x * o.x + y * o.y;
        }

        constexpr float LengthSquared() const
        {
            return x * x + y * y;
        }

        float Length() const
        {
            return std::sqrt(LengthSquared());
        }

        Vector2 Normalized() const
        {
            const float len = Length();
            return len > 0.0f ? Vector2{x / len, y / len} : Vector2{};
        }

        Vector2 Rotated(float radians) const
        {
            const float c = std::cos(radians);
            const float s = std::sin(radians);
            return {x * c - y * s, x * s + y * c};
        }

        static float Distance(Vector2 a, Vector2 b) { return (a - b).Length(); }
    };

}