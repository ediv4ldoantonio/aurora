#pragma once

#include "Aurora/Renderer/PostProcessEffect.h"
#include "Aurora/Renderer/Texture2D.h"
#include "Aurora/Renderer/PostProcessSettings.h"
#include "Aurora/Renderer/Framebuffer.h"
#include "Aurora/Renderer/PostProcessPass.h"

#include <vector>
#include <memory>
#include <unordered_map>

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

        static void SetEffects(
            const std::vector<PostProcessEffect> &effects);

        static const std::vector<PostProcessEffect> &
        GetEffects();

        static void Apply(
            const std::shared_ptr<Texture2D> &source);

        static void Resize(
            uint32_t width,
            uint32_t height);

    private:
        static PostProcessPass *
        FindPass(
            PostProcessEffect effect);

        static void InitShaders();

        static RendererAPI *s_Renderer;

        static PostProcessEffect s_Effect;

        static std::vector<PostProcessEffect>
            s_Effects;

        static std::shared_ptr<Framebuffer>
            s_PingFramebuffer;

        static std::shared_ptr<Framebuffer>
            s_PongFramebuffer;

        static std::unordered_map<
            PostProcessEffect,
            PostProcessPass>
            s_Passes;
    };
}