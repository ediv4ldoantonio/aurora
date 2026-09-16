#include "Aurora/Renderer/PostProcessPass.h"
#include "Aurora/Renderer/RendererAPI.h"

namespace Aurora
{
    PostProcessPass::PostProcessPass(
        RendererAPI *renderer)
        : m_Renderer(renderer)
    {
    }

    void PostProcessPass::SetRenderer(
        RendererAPI *renderer)
    {
        m_Renderer = renderer;
    }

    void PostProcessPass::Apply(
        const std::shared_ptr<Texture2D> &source,
        const std::shared_ptr<Framebuffer> &target,
        PostProcessEffect effect,
        const PostProcessSettings &settings)
    {
        if (!m_Renderer)
            return;

        if (!source)
            return;

        if (!target)
            return;

        m_Renderer->SetPostProcessEffect(effect);
        m_Renderer->SetPostProcessSettings(settings);

        m_Renderer->DrawFramebuffer(
            source,
            target);
    }
}