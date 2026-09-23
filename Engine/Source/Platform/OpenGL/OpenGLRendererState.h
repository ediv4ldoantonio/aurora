#pragma once

#include "Aurora/Renderer/BlendMode.h"

#include <cstdint>
#include <array>
#include <memory>

namespace Aurora
{
    class Shader;
    class Texture2D;
    class VertexArray;

    struct OpenGLRendererState
    {
        const Shader *CurrentShader = nullptr;
        const VertexArray *CurrentVertexArray = nullptr;

        std::array<std::shared_ptr<Texture2D>, 16> TextureBindings{};

        BlendMode CurrentBlendMode = BlendMode::Opaque;

        bool HasBlendMode = false;

        int ViewportX = 0;
        int ViewportY = 0;
        int ViewportWidth = 0;
        int ViewportHeight = 0;

        bool HasViewport = false;

        float ClearColorR = 0.0f;
        float ClearColorG = 0.0f;
        float ClearColorB = 0.0f;
        float ClearColorA = 0.0f;

        bool HasClearColor = false;
    };
}