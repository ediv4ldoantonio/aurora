#include "Aurora/Math/Matrix4.h"

#include <cmath>

namespace Aurora
{
    Matrix4::Matrix4()
    {
        for (int row = 0; row < 4; ++row)
        {
            for (int column = 0; column < 4; ++column)
            {
                m_Data[row][column] = 0.0f;
            }
        }
    }

    Matrix4 Matrix4::Identity()
    {
        Matrix4 result;

        result[0][0] = 1.0f;
        result[1][1] = 1.0f;
        result[2][2] = 1.0f;
        result[3][3] = 1.0f;

        return result;
    }

    Matrix4 Matrix4::Translation(
        const Vector2 &position)
    {
        Matrix4 result =
            Matrix4::Identity();

        result[0][3] = position.x;
        result[1][3] = position.y;

        return result;
    }

    Matrix4 Scale(
        const Vector2 &scale)
    {
        Matrix4 result =
            Matrix4::Identity();

        result[0][0] = scale.x;
        result[1][1] = scale.y;

        return result;
    }

    Matrix4 Matrix4::Rotation(
        float angle)
    {
        Matrix4 result =
            Matrix4::Identity();

        float cosine =
            std::cos(angle);

        float sine =
            std::sin(angle);

        result[0][0] = cosine;
        result[0][1] = -sine;

        result[1][0] = sine;
        result[1][1] = cosine;

        return result;
    }

    Matrix4 Matrix4::Orthographic(
        float left,
        float right,
        float bottom,
        float top,
        float near,
        float far)
    {
        Matrix4 result;

        result[0][0] =
            2.0f / (right - left);

        result[1][1] =
            2.0f / (top - bottom);

        result[2][2] =
            -2.0f / (far - near);

        result[0][3] =
            -(right + left) /
            (right - left);

        result[1][3] =
            -(top + bottom) /
            (top - bottom);

        result[2][3] =
            -(far + near) /
            (far - near);

        result[3][3] = 1.0f;

        return result;
    }

    float *Matrix4::operator[](int row)
    {
        return m_Data[row];
    }

    const float *Matrix4::operator[](int row) const
    {
        return m_Data[row];
    }

    Matrix4 Matrix4::operator*(
        const Matrix4 &other) const
    {
        Matrix4 result;

        for (int row = 0; row < 4; ++row)
        {
            for (int column = 0; column < 4; ++column)
            {
                for (int i = 0; i < 4; ++i)
                {
                    result[row][column] +=
                        m_Data[row][i] *
                        other[i][column];
                }
            }
        }

        return result;
    }

    Vector2 Matrix4::TransformPoint(
        const Vector2 &point) const
    {
        float x =
            m_Data[0][0] * point.x +
            m_Data[0][1] * point.y +
            m_Data[0][3];

        float y =
            m_Data[1][0] * point.x +
            m_Data[1][1] * point.y +
            m_Data[1][3];

        return Vector2(x, y);
    }
}