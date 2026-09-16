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
        if (zoom <= 0.0f)
        {
            return;
        }

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
        if (m_ViewportSize.x <= 0.0f ||
            m_ViewportSize.y <= 0.0f)
        {
            return;
        }

        const float aspect =
            m_ViewportSize.x /
            m_ViewportSize.y;

        const float halfHeight =
            m_OrthographicSize /
            m_Zoom;

        const float halfWidth =
            halfHeight * aspect;

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
        if (m_ViewportSize.x <= 0.0f ||
            m_ViewportSize.y <= 0.0f)
        {
            return {};
        }

        const Vector2 viewSpacePosition =
            m_ViewMatrix.TransformPoint(
                worldPosition);

        const Vector2 normalizedPosition =
            m_ProjectionMatrix.TransformPoint(
                viewSpacePosition);

        return Vector2(
            (normalizedPosition.x + 1.0f) *
                0.5f * m_ViewportSize.x,
            (1.0f - normalizedPosition.y) *
                0.5f * m_ViewportSize.y);
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