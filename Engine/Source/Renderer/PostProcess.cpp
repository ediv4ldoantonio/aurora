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

    std::shared_ptr<Framebuffer>
        PostProcess::s_IntermediateFramebuffer = nullptr;

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
        s_Effect = PostProcessEffect::None;
        s_Settings = PostProcessSettings{};

        FramebufferSpecification specification;
        specification.Width = width;
        specification.Height = height;
        specification.HasDepthStencil = false;

        s_IntermediateFramebuffer =
            RendererResourceFactory::CreateFramebuffer(
                specification);
    }

    void PostProcess::Shutdown()
    {
        s_IntermediateFramebuffer.reset();

        s_Renderer = nullptr;

        s_Effect = PostProcessEffect::None;

        s_Settings = PostProcessSettings{};
    }

    void PostProcess::SetEffect(
        PostProcessEffect effect)
    {
        s_Effect = effect;
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

        s_Renderer->SetPostProcessEffect(
            s_Effect);

        s_Renderer->SetPostProcessSettings(s_Settings);

        s_Renderer->DrawFramebuffer(source);
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
        if (!s_IntermediateFramebuffer)
            return;

        if (width == 0 || height == 0)
            return;

        s_IntermediateFramebuffer->Resize(
            width,
            height);
    }
}