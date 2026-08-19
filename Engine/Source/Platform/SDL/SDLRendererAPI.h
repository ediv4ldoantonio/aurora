#pragma once

#include "Aurora/Renderer/RendererAPI.h"
#include "Aurora/Scene/Components/SpriteComponent.h"
#include "Aurora/Scene/Components/TransformComponent.h"

struct SDL_Renderer;

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

        void *GetNativeRenderer() override;

    private:
        SDL_Renderer *m_Renderer;
    };

}