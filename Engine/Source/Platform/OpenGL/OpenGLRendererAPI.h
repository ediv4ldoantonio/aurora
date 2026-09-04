#pragma once

#include "Aurora/Renderer/RendererAPI.h"
#include "Aurora/Renderer/RendererBackend.h"

namespace Aurora
{
    class OpenGLRendererAPI : public RendererAPI
    {
    public:
        void Init() override;

        void BeginFrame() override;

        void EndFrame() override;

        void Shutdown() override;

        void DrawSprite(
            const SpriteDrawCommand &command) override;

        void Clear() override;

        void SetViewport(
            int x,
            int y,
            int width,
            int height) override;

        void DrawSpriteBatch(
            const SpriteBatch &batch) override;

        void *GetNativeRenderer() override;

        RendererBackend GetBackend() const override;
    };
}
