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

    bool PostProcessPass::Apply(
        const std::shared_ptr<Texture2D> &source,
        const std::shared_ptr<Framebuffer> &target)
    {
        if (!m_Enabled)
            return false;

        if (!m_Renderer)
            return false;

        if (!source)
            return false;

        if (!target)
            return false;

        if (!m_Shader)
            return false;

        m_Shader->Bind();

        for (const auto &[name, value] :
             m_FloatUniforms)
        {
            m_Shader->SetFloat(
                name,
                value);
        }

        for (const auto &[name, value] :
             m_IntUniforms)
        {
            m_Shader->SetInt(
                name,
                value);
        }

        for (const auto &[name, value] :
             m_Vector2Uniforms)
        {
            m_Shader->SetVector2(
                name,
                value);
        }

        m_Shader->Unbind();

        m_Renderer->DrawPostProcess(
            source,
            target,
            m_Shader);

        return true;
    }

    void PostProcessPass::SetFloat(
        const std::string &name,
        float value)
    {
        m_FloatUniforms[name] = value;
    }

    void PostProcessPass::SetInt(
        const std::string &name,
        int value)
    {
        m_IntUniforms[name] = value;
    }

    void PostProcessPass::SetVector2(
        const std::string &name,
        const Vector2 &value)
    {
        m_Vector2Uniforms[name] =
            value;
    }

    void PostProcessPass::SetEnabled(
        bool enabled)
    {
        m_Enabled = enabled;
    }

    bool PostProcessPass::IsEnabled() const
    {
        return m_Enabled;
    }
}