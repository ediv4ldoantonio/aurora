#pragma once

#include "Aurora/Math/Vector2.h"
#include "Aurora/Renderer/SpriteDrawCommand.h"

namespace Aurora
{

    class RendererAPI
    {

    public:
        virtual ~RendererAPI() = default;

        virtual void Init() = 0;

        virtual void BeginFrame() = 0;

        virtual void EndFrame() = 0;

        virtual void DrawSprite(
            const SpriteDrawCommand &command) = 0;

        virtual void *GetNativeRenderer() = 0;
    };

}