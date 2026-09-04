#pragma once

#include <SDL3/SDL_blendmode.h>

#include "Aurora/Renderer/RendererAPI.h"
#include "Aurora/Renderer/RendererState.h"
#include "Aurora/Renderer/RendererBackend.h"

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

    private:
        SDL_Renderer *m_Renderer;
        RendererState m_State;
        uint32_t m_DrawCallCount = 0;

        static SDL_BlendMode ToSDLBlendMode(
            Aurora::BlendMode mode);

        static SDL_Vertex ToSDLVertex(
            const SpriteVertex &vertex);

        static void ApplyTextureMaterial(
            SDL_Texture *texture,
            const Material &material);

        void ApplyMaterialState(
            Material *material);

        void DrawMaterialRange(
            const SpriteBatch &batch,
            size_t firstQuad,
            size_t quadCount,
            Material *material);

        uint32_t GetDrawCallCount() const;
    };
}