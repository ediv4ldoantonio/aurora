#include "Aurora/Renderer/Material.h"

#include <utility>

namespace Aurora
{
    UUID Material::GetID() const
    {
        return m_ID;
    }

    Material::Material(
        std::shared_ptr<Texture2D> texture)
        : m_Texture(
              std::move(texture))
    {
    }

    void Material::SetTexture(
        std::shared_ptr<Texture2D> texture)
    {
        m_Texture =
            std::move(texture);
    }

    const std::shared_ptr<Texture2D> &
    Material::GetTexture() const
    {
        return m_Texture;
    }

    void Material::SetTint(
        const Color &tint)
    {
        m_Tint = tint;
    }

    const Color &
    Material::GetTint() const
    {
        return m_Tint;
    }

    void Material::SetBlendMode(
        BlendMode mode)
    {
        m_BlendMode = mode;
    }

    BlendMode Material::GetBlendMode() const
    {
        return m_BlendMode;
    }

    bool Material::IsOpaque() const
    {
        return m_BlendMode ==
               BlendMode::Opaque;
    }
}