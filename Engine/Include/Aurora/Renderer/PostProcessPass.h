#pragma once

#include "Aurora/Renderer/Framebuffer.h"
#include "Aurora/Renderer/PostProcessEffect.h"
#include "Aurora/Renderer/PostProcessSettings.h"
#include "Aurora/Renderer/Texture2D.h"

#include <memory>

namespace Aurora
{
    class RendererAPI;

    class PostProcessPass
    {
    public:
        PostProcessPass() = default;

        explicit PostProcessPass(
            RendererAPI *renderer);

        void SetRenderer(
            RendererAPI *renderer);

        void Apply(
            const std::shared_ptr<Texture2D> &source,
            const std::shared_ptr<Framebuffer> &target,
            PostProcessEffect effect,
            const PostProcessSettings &settings);

    private:
        RendererAPI *m_Renderer = nullptr;
    };
}