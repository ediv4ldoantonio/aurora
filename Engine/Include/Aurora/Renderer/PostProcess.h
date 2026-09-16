#pragma once

#include "Aurora/Renderer/PostProcessEffect.h"
#include "Aurora/Renderer/Texture2D.h"
#include "Aurora/Renderer/PostProcessSettings.h"
#include "Aurora/Renderer/Framebuffer.h"

#include <memory>

namespace Aurora
{
    class RendererAPI;

    class PostProcess
    {
    public:
        static void Init(
            RendererAPI *renderer,
            uint32_t width,
            uint32_t height);
        static void Shutdown();

        static void SetEffect(
            PostProcessEffect effect);

        static PostProcessEffect GetEffect();

        static void Apply(
            const std::shared_ptr<Texture2D> &source);

        static void SetSettings(
            const PostProcessSettings &settings);

        static const PostProcessSettings &
        GetSettings();

        static void Resize(
            uint32_t width,
            uint32_t height);

    private:
        static RendererAPI *s_Renderer;

        static PostProcessEffect s_Effect;
        static PostProcessSettings s_Settings;

        static std::shared_ptr<Framebuffer>
            s_IntermediateFramebuffer;
    };
}