#include "Aurora/Renderer/Material.h"

namespace Aurora
{
    Material::Material(
        Texture2D *texture)
        : m_Texture(texture)
    {
    }

    void Material::SetTexture(
        Texture2D *texture)
    {
        m_Texture = texture;
    }

    Texture2D *Material::GetTexture() const
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
}