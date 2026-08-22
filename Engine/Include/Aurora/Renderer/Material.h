#pragma once

#include "Aurora/Core/UUID.h"
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

        void SetBlendMode(
            BlendMode mode);

        BlendMode GetBlendMode() const;

    private:
        UUID m_ID;

        std::shared_ptr<Texture2D> m_Texture;

        Color m_Tint;

        BlendMode m_BlendMode =
            BlendMode::Opaque;
    };
}