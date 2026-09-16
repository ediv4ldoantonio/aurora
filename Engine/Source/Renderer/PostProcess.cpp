#include "Aurora/Renderer/PostProcess.h"
#include "Aurora/Renderer/RendererAPI.h"

#include <stdexcept>

namespace Aurora
{
    RendererAPI *PostProcess::s_Renderer = nullptr;

    PostProcessEffect PostProcess::s_Effect =
        PostProcessEffect::None;

    void PostProcess::Init(RendererAPI *renderer)
    {
        if (!renderer)
        {
            throw std::invalid_argument(
                "PostProcess received null RendererAPI");
        }

        s_Renderer = renderer;
        s_Effect = PostProcessEffect::None;
    }

    void PostProcess::Shutdown()
    {
        s_Renderer = nullptr;
        s_Effect = PostProcessEffect::None;
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

        s_Renderer->DrawFramebuffer(source);
    }
}