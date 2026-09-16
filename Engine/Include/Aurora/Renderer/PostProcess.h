#pragma once

#include "Aurora/Renderer/PostProcessEffect.h"
#include "Aurora/Renderer/Texture2D.h"
#include "Aurora/Renderer/PostProcessSettings.h"

#include <memory>

namespace Aurora
{
    class RendererAPI;

    class PostProcess
    {
    public:
        static void Init(RendererAPI *renderer);
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

    private:
        static RendererAPI *s_Renderer;
        static PostProcessEffect s_Effect;
        static PostProcessSettings s_Settings;
    };
}