#include "Aurora/Renderer/Camera2D.h"
#include <cmath>

namespace Aurora
{
    Camera2D::Camera2D()
    {
        RecalculateViewMatrix();
        RecalculateProjectionMatrix();
    }

    void Camera2D::SetPosition(
        const Vector2 &position)
    {
        m_Position = position;

        RecalculateViewMatrix();
    }

    const Vector2 &
    Camera2D::GetPosition() const
    {
        return m_Position;
    }

    void Camera2D::SetViewportSize(
        const Vector2 &size)
    {
        m_ViewportSize = size;

        RecalculateProjectionMatrix();
    }

    const Vector2 &
    Camera2D::GetViewportSize() const
    {
        return m_ViewportSize;
    }

    void Camera2D::SetZoom(
        float zoom)
    {
        m_Zoom = zoom;

        RecalculateProjectionMatrix();
    }

    float Camera2D::GetZoom() const
    {
        return m_Zoom;
    }

    const Matrix4 &
    Camera2D::GetViewMatrix() const
    {
        return m_ViewMatrix;
    }

    const Matrix4 &
    Camera2D::GetProjectionMatrix() const
    {
        return m_ProjectionMatrix;
    }

    Matrix4 Camera2D::GetViewProjectionMatrix() const
    {
        return m_ProjectionMatrix *
               m_ViewMatrix;
    }

    void Camera2D::RecalculateViewMatrix()
    {
        Matrix4 translation =
            Matrix4::Translation(
                Vector2(
                    -m_Position.x,
                    -m_Position.y));

        Matrix4 rotation =
            Matrix4::Rotation(
                -m_Rotation);

        m_ViewMatrix =
            rotation *
            translation;
    }

    void Camera2D::RecalculateProjectionMatrix()
    {
        float halfWidth =
            (m_ViewportSize.x * 0.5f) /
            m_Zoom;

        float halfHeight =
            (m_ViewportSize.y * 0.5f) /
            m_Zoom;

        m_ProjectionMatrix =
            Matrix4::Orthographic(
                -halfWidth,
                halfWidth,
                -halfHeight,
                halfHeight,
                -1.0f,
                1.0f);
    }

    Vector2 Camera2D::WorldToScreen(
        const Vector2 &worldPosition) const
    {
        Vector2 relative =
            worldPosition - m_Position;

        float radians =
            -m_Rotation;

        float cosRotation =
            std::cos(radians);

        float sinRotation =
            std::sin(radians);

        Vector2 rotated;

        rotated.x =
            relative.x * cosRotation -
            relative.y * sinRotation;

        rotated.y =
            relative.x * sinRotation +
            relative.y * cosRotation;

        rotated.x *= m_Zoom;
        rotated.y *= m_Zoom;

        Vector2 screen;

        screen.x =
            m_ViewportSize.x * 0.5f +
            rotated.x;

        screen.y =
            m_ViewportSize.y * 0.5f -
            rotated.y;

        return screen;
    }

    void Camera2D::SetRotation(
        float rotation)
    {
        m_Rotation = rotation;

        RecalculateViewMatrix();
    }

    float Camera2D::GetRotation() const
    {
        return m_Rotation;
    }
}