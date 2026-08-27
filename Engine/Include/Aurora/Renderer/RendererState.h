#pragma once

#include "Aurora/Renderer/BlendMode.h"
#include "Aurora/Renderer/Color.h"

namespace Aurora
{
    class Texture2D;

    struct RendererState
    {
        Texture2D *Texture = nullptr;

        Color Tint =
            Color::White;

        BlendMode Blend =
            BlendMode::Opaque;

        bool operator==(
            const RendererState &other) const
        {
            return Texture == other.Texture &&
                   Tint == other.Tint &&
                   Blend == other.Blend;
        }

        bool operator!=(
            const RendererState &other) const
        {
            return !(*this == other);
        }
    };
}