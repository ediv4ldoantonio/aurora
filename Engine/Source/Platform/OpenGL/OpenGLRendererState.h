#pragma once

#include "Aurora/Renderer/BlendMode.h"

#include <cstdint>
#include <array>

namespace Aurora
{
    class Shader;
    class Texture2D;

    struct OpenGLRendererState
    {
        const Shader *CurrentShader = nullptr;

        std::array<const Texture2D *, 16> TextureBindings{};

        BlendMode CurrentBlendMode = BlendMode::Opaque;

        bool HasBlendMode = false;

        int ViewportX = 0;
        int ViewportY = 0;
        int ViewportWidth = 0;
        int ViewportHeight = 0;

        bool HasViewport = false;
    };
}