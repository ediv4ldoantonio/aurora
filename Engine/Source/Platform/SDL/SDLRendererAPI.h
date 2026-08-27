#pragma once

#include <SDL3/SDL_blendmode.h>

#include "Aurora/Renderer/RendererAPI.h"

struct SDL_Renderer;
struct SDL_Vertex;
struct SDL_Texture;

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

        static SDL_BlendMode ToSDLBlendMode(
            Aurora::BlendMode mode);

        static void ApplyTextureMaterial(
            SDL_Texture *texture,
            const Material &material);
    };
}