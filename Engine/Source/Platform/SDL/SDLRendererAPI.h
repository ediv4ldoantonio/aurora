#pragma once

#include "Aurora/Renderer/RendererAPI.h"

struct SDL_Renderer;
struct SDL_Vertex;

namespace Aurora
{

    class SDLRendererAPI : public RendererAPI
    {

    public:
        explicit SDLRendererAPI(
            SDL_Renderer *renderer);

        void Init() override;

        void BeginFrame() override;

        void EndFrame() override;

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

        static SDL_Vertex ToSDLVertex(
            const SpriteVertex &vertex);

    private:
        SDL_Renderer *m_Renderer;
    };
}