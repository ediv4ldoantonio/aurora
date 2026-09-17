#include "Aurora/Renderer/PostProcess.h"
#include "Aurora/Renderer/RendererAPI.h"
#include "Aurora/Renderer/RendererResourceFactory.h"

#include <stdexcept>

namespace Aurora
{
    RendererAPI *PostProcess::s_Renderer = nullptr;

    PostProcessEffect PostProcess::s_Effect =
        PostProcessEffect::None;

    PostProcessSettings PostProcess::s_Settings;

    PostProcessPass PostProcess::s_Pass;

    std::shared_ptr<Framebuffer>
        PostProcess::s_PingFramebuffer = nullptr;

    std::shared_ptr<Framebuffer>
        PostProcess::s_PongFramebuffer = nullptr;

    std::vector<PostProcessEffect>
        PostProcess::s_Effects;

    void PostProcess::Init(
        RendererAPI *renderer,
        uint32_t width,
        uint32_t height)
    {
        if (!renderer)
        {
            throw std::invalid_argument(
                "PostProcess received null RendererAPI");
        }

        s_Renderer = renderer;

        s_Pass.SetRenderer(
            s_Renderer);

        s_Effect = PostProcessEffect::None;
        s_Settings = PostProcessSettings{};
        s_Effects.clear();

        FramebufferSpecification specification;
        specification.Width = width;
        specification.Height = height;
        specification.HasDepthStencil = false;

        s_PingFramebuffer =
            RendererResourceFactory::CreateFramebuffer(
                specification);

        s_PongFramebuffer =
            RendererResourceFactory::CreateFramebuffer(
                specification);
    }

    void PostProcess::Shutdown()
    {
        s_PingFramebuffer.reset();

        s_PongFramebuffer.reset();

        s_Pass.SetRenderer(nullptr);

        s_Renderer = nullptr;

        s_Effect =
            PostProcessEffect::None;

        s_Settings =
            PostProcessSettings{};
    }

    void PostProcess::SetEffect(
        PostProcessEffect effect)
    {
        s_Effect = effect;

        s_Effects.clear();

        if (effect != PostProcessEffect::None)
            s_Effects.push_back(effect);
    }

    void PostProcess::SetEffects(
        const std::vector<PostProcessEffect> &effects)
    {
        s_Effects = effects;

        if (s_Effects.empty())
        {
            s_Effect =
                PostProcessEffect::None;

            return;
        }

        s_Effect =
            s_Effects.front();
    }

    const std::vector<PostProcessEffect> &
    PostProcess::GetEffects()
    {
        return s_Effects;
    }

    PostProcessEffect PostProcess::GetEffect()
    {
        return s_Effect;
    }

    void PostProcess::Apply(
        const std::shared_ptr<Texture2D> &source)
    {
        if (!s_Renderer)
            return;

        if (!source)
            return;

        if (s_Effects.empty())
        {
            s_Renderer->DrawFramebuffer(
                source);

            return;
        }

        if (!s_PingFramebuffer ||
            !s_PongFramebuffer)
        {
            s_Renderer->DrawFramebuffer(
                source);

            return;
        }

        std::shared_ptr<Texture2D>
            currentSource = source;

        bool ping = true;

        for (const auto effect :
             s_Effects)
        {
            if (effect ==
                PostProcessEffect::None)
            {
                continue;
            }

            const auto &target =
                ping
                    ? s_PingFramebuffer
                    : s_PongFramebuffer;

            s_Pass.Apply(
                currentSource,
                target,
                effect,
                s_Settings);

            currentSource =
                target->GetColorAttachment();

            ping = !ping;
        }

        s_Renderer->DrawFramebuffer(
            currentSource);
    }

    void PostProcess::SetSettings(
        const PostProcessSettings &settings)
    {
        s_Settings = settings;
    }

    const PostProcessSettings &
    PostProcess::GetSettings()
    {
        return s_Settings;
    }

    void PostProcess::Resize(
        uint32_t width,
        uint32_t height)
    {
        if (!s_PingFramebuffer ||
            !s_PongFramebuffer)
            return;

        if (width == 0 || height == 0)
            return;

        s_PingFramebuffer->Resize(
            width,
            height);

        s_PongFramebuffer->Resize(
            width,
            height);
    }
}