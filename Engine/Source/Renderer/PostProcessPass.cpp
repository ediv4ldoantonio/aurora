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

        m_ScreenTextureUniformInitialized = false;

        for (auto &[name, uniform] : m_FloatUniforms)
            uniform.Dirty = true;

        for (auto &[name, uniform] : m_IntUniforms)
            uniform.Dirty = true;

        for (auto &[name, uniform] : m_Vector2Uniforms)
            uniform.Dirty = true;
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

        InitializeScreenTextureUniform();

        m_Shader->Bind();

        for (auto &[name, uniform] : m_FloatUniforms)
        {
            if (!uniform.Dirty)
                continue;

            m_Shader->SetFloat(
                name,
                uniform.Value);

            uniform.Dirty = false;
        }

        for (auto &[name, uniform] : m_IntUniforms)
        {
            if (!uniform.Dirty)
                continue;

            m_Shader->SetInt(
                name,
                uniform.Value);

            uniform.Dirty = false;
        }

        for (auto &[name, uniform] : m_Vector2Uniforms)
        {
            if (!uniform.Dirty)
                continue;

            m_Shader->SetVector2(
                name,
                uniform.Value);

            uniform.Dirty = false;
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
        auto it =
            m_FloatUniforms.find(name);

        if (it == m_FloatUniforms.end())
        {
            m_FloatUniforms.emplace(
                name,
                FloatUniform{
                    value,
                    true});
            return;
        }

        if (it->second.Value == value)
            return;

        it->second.Value = value;
        it->second.Dirty = true;
    }

    void PostProcessPass::SetInt(
        const std::string &name,
        int value)
    {
        auto it =
            m_IntUniforms.find(name);

        if (it == m_IntUniforms.end())
        {
            m_IntUniforms.emplace(
                name,
                IntUniform{
                    value,
                    true});
            return;
        }

        if (it->second.Value == value)
            return;

        it->second.Value = value;
        it->second.Dirty = true;
    }

    void PostProcessPass::SetVector2(
        const std::string &name,
        const Vector2 &value)
    {
        auto it =
            m_Vector2Uniforms.find(name);

        if (it == m_Vector2Uniforms.end())
        {
            m_Vector2Uniforms.emplace(
                name,
                Vector2Uniform{
                    value,
                    true});
            return;
        }

        if (it->second.Value.x == value.x &&
            it->second.Value.y == value.y)
        {
            return;
        }

        it->second.Value = value;
        it->second.Dirty = true;
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

    void PostProcessPass::InitializeScreenTextureUniform()
    {
        if (m_ScreenTextureUniformInitialized)
            return;

        if (!m_Shader)
            return;

        m_Shader->Bind();

        m_Shader->SetInt(
            "u_ScreenTexture",
            0);

        m_Shader->Unbind();

        m_ScreenTextureUniformInitialized = true;
    }
}