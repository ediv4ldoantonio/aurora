#pragma once

#include "Aurora/Math/Vector2.h"

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

        Vector2 WorldToScreen(
            const Vector2 &worldPosition) const;

    private:
        Vector2 m_Position;

        Vector2 m_ViewportSize;

        float m_Zoom;
    };

}