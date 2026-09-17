#include "Aurora/Renderer/PostProcessPass.h"
#include "Aurora/Renderer/RendererAPI.h"

namespace Aurora
{
    PostProcessPass::PostProcessPass(
        RendererAPI *renderer,
        PostProcessEffect effect,
        std::shared_ptr<Shader> shader)
        : m_Renderer(renderer),
          m_Effect(effect),
          m_Shader(std::move(shader))
    {
    }

    void PostProcessPass::SetRenderer(
        RendererAPI *renderer)
    {
        m_Renderer = renderer;
    }

    void PostProcessPass::SetShader(
        const std::shared_ptr<Shader> &shader)
    {
        m_Shader = shader;
    }

    PostProcessEffect
    PostProcessPass::GetEffect() const
    {
        return m_Effect;
    }

    void PostProcessPass::Apply(
        const std::shared_ptr<Texture2D> &source,
        const std::shared_ptr<Framebuffer> &target)
    {
        if (!m_Renderer)
            return;

        if (!source)
            return;

        if (!target)
            return;

        if (!m_Shader)
            return;

        m_Renderer->DrawPostProcess(
            source,
            target,
            m_Shader);
    }
}