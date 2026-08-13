#include "Aurora/Renderer/Camera2D.h"

namespace Aurora
{

    Camera2D::Camera2D()
        : m_Position(0.0f, 0.0f),
          m_ViewportSize(1280.0f, 720.0f)
    {
    }

    void Camera2D::SetPosition(
        const Vector2 &position)
    {
        m_Position = position;
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
    }

    const Vector2 &
    Camera2D::GetViewportSize() const
    {
        return m_ViewportSize;
    }

    Vector2 Camera2D::WorldToScreen(
        const Vector2 &worldPosition) const
    {
        Vector2 relative =
            worldPosition - m_Position;

        return relative +
               m_ViewportSize * 0.5f;
    }

}