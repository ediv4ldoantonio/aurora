#pragma once

namespace Aurora
{

    struct Vector2
    {

        float x = 0.0f;
        float y = 0.0f;

        Vector2() = default;

        Vector2(
            float x,
            float y)
            : x(x),
              y(y)
        {
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

        Vector2 &operator*=(float value)
        {
            x *= value;
            y *= value;
            return *this;
        }
    };

}