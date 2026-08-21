#pragma once

#include "Aurora/Renderer/BlendMode.h"
#include "Aurora/Renderer/Color.h"

namespace Aurora
{
    class Texture2D;

    class Material
    {
    public:
        Material() = default;

        explicit Material(
            Texture2D *texture);

        void SetTexture(
            Texture2D *texture);

        Texture2D *GetTexture() const;

        void SetTint(
            const Color &tint);

        const Color &GetTint() const;

        void SetBlendMode(
            BlendMode mode);

        BlendMode GetBlendMode() const;

    private:
        Texture2D *m_Texture = nullptr;

        Color m_Tint;

        BlendMode m_BlendMode =
            BlendMode::Opaque;
    };
}