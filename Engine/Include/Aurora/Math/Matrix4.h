#pragma once

#include "Aurora/Math/Vector2.h"

namespace Aurora
{
    class Matrix4
    {
    public:
        Matrix4();

        static Matrix4 Identity();

        static Matrix4 Translation(
            const Vector2 &position);

        static Matrix4 Scale(
            const Vector2 &scale);

        static Matrix4 Orthographic(
            float left,
            float right,
            float bottom,
            float top,
            float near,
            float far);

        static Matrix4 Rotation(
            float angle);

        Matrix4 operator*(
            const Matrix4 &other) const;

        float *operator[](int row);

        const float *operator[](int row) const;

        Vector2 TransformPoint(
            const Vector2 &point) const;

    private:
        float m_Data[4][4];
    };
}