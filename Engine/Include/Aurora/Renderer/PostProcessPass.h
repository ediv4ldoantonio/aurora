#pragma once

#include "Aurora/Renderer/Texture2D.h"
#include "Aurora/Renderer/Framebuffer.h"

#include <memory>

namespace Aurora
{
    class RendererAPI;

    class PostProcessPass
    {
    public:
        PostProcessPass() = default;
        explicit PostProcessPass(RendererAPI *renderer);

        void SetRenderer(RendererAPI *renderer);

        void SetEffect(int effect);

        void Apply(
            const std::shared_ptr<Texture2D> &source,
            const std::shared_ptr<Framebuffer> &target);

    private:
        RendererAPI *m_Renderer = nullptr;
        int m_Effect = 0;
    };
}