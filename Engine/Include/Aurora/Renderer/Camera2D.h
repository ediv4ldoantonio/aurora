#pragma once

#include "Aurora/Math/Vector2.h"
#include "Aurora/Math/Matrix4.h"

namespace Aurora
{
    class Camera2D
    {
    public:
        Camera2D();

        void SetPosition(
            const Vector2 &position);

        const Vector2 &
        GetPosition() const;

        void SetViewportSize(
            const Vector2 &size);

        const Vector2 &
        GetViewportSize() const;

        void SetZoom(
            float zoom);

        float GetZoom() const;

        const Matrix4 &
        GetViewMatrix() const;

        const Matrix4 &
        GetProjectionMatrix() const;

        Matrix4 GetViewProjectionMatrix() const;

        Vector2 WorldToScreen(
            const Vector2 &worldPosition) const;

        void SetRotation(float rotation);

        float GetRotation() const;

    private:
        void RecalculateViewMatrix();

        void RecalculateProjectionMatrix();

    private:
        float m_Rotation = 0.0f;
        float m_Zoom = 1.0f;

        Vector2 m_Position;
        Vector2 m_ViewportSize =
            {1280.0f, 720.0f};

        Matrix4 m_ViewMatrix =
            Matrix4::Identity();

        Matrix4 m_ProjectionMatrix =
            Matrix4::Identity();
    };
}