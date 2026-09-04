#pragma once

#include "Aurora/Math/Vector2.h"
#include "Aurora/Renderer/SpriteDrawCommand.h"
#include "Aurora/Renderer/SpriteBatch.h"
#include "Aurora/Renderer/RendererBackend.h"

namespace Aurora
{

    class RendererAPI
    {

    public:
        virtual ~RendererAPI() = default;

        virtual void Init() = 0;

        virtual void BeginFrame() = 0;

        virtual void EndFrame() = 0;

        virtual void Shutdown() = 0;

        virtual void DrawSprite(
            const SpriteDrawCommand &command) = 0;

        virtual void Clear() = 0;

        virtual void SetViewport(
            int x,
            int y,
            int width,
            int height) = 0;

        virtual void DrawSpriteBatch(
            const SpriteBatch &batch) = 0;

        virtual void *GetNativeRenderer() = 0;

        virtual RendererBackend
        GetBackend() const = 0;

    private:
        static RendererBackend s_Backend;
    };

}