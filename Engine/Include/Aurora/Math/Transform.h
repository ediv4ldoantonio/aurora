#pragma once

#include "Aurora/Math/Vector2.h"
#include "Aurora/Math/Matrix4.h"

namespace Aurora
{
    class Transform
    {
    public:
        Transform() = default;

        Transform(
            const Vector2 &position,
            float rotation = 0.0f,
            const Vector2 &scale = {1.0f, 1.0f});

        Matrix4 ToMatrix() const;

    public:
        Vector2 Position;

        float Rotation = 0.0f;

        Vector2 Scale = {1.0f, 1.0f};
    };
}