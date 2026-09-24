#pragma once

#include "Aurora/Core/UUID.h"
#include "Aurora/Math/Vector2.h"
#include "Aurora/Renderer/BlendMode.h"
#include "Aurora/Renderer/Color.h"

#include <memory>

namespace Aurora
{
    class Texture2D;

    class Material
    {
    public:
        Material() = default;

        explicit Material(
            std::shared_ptr<Texture2D> texture);

        UUID GetID() const;

        void SetTexture(
            std::shared_ptr<Texture2D> texture);

        const std::shared_ptr<Texture2D> &
        GetTexture() const;

        void SetTint(
            const Color &tint);

        const Color &
        GetTint() const;

        void SetScale(
            const Vector2 &scale);

        const Vector2 &
        GetScale() const;

        void SetBlendMode(
            BlendMode mode);

        BlendMode GetBlendMode() const;

        bool IsOpaque() const;

    private:
        UUID m_ID;

        std::shared_ptr<Texture2D> m_Texture;

        Color m_Tint;

        Vector2 m_Scale =
            Vector2::One();

        BlendMode m_BlendMode =
            BlendMode::Opaque;
    };
}