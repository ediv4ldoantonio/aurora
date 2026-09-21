#pragma once

#include "Aurora/Renderer/Framebuffer.h"
#include "Aurora/Renderer/PostProcessEffect.h"
#include "Aurora/Renderer/Shader.h"
#include "Aurora/Renderer/Texture2D.h"
#include "Aurora/Math/Vector2.h"

#include <memory>
#include <string>
#include <unordered_map>

namespace Aurora
{
    class RendererAPI;

    class PostProcessPass
    {
    public:
        PostProcessPass() = default;

        PostProcessPass(
            RendererAPI *renderer,
            PostProcessEffect effect,
            std::shared_ptr<Shader> shader);

        void SetRenderer(
            RendererAPI *renderer);

        void SetShader(
            const std::shared_ptr<Shader> &shader);

        PostProcessEffect GetEffect() const;

        void SetFloat(
            const std::string &name,
            float value);

        void SetInt(
            const std::string &name,
            int value);

        bool Apply(
            const std::shared_ptr<Texture2D> &source,
            const std::shared_ptr<Framebuffer> &target);

        void SetVector2(
            const std::string &name,
            const Vector2 &value);

        void SetEnabled(
            bool enabled);

        bool IsEnabled() const;

    private:
        bool m_Enabled = true;

        RendererAPI *m_Renderer = nullptr;

        PostProcessEffect m_Effect =
            PostProcessEffect::None;

        std::shared_ptr<Shader> m_Shader;

        std::unordered_map<std::string, float>
            m_FloatUniforms;

        std::unordered_map<std::string, int>
            m_IntUniforms;

        std::unordered_map<std::string, Vector2>
            m_Vector2Uniforms;
    };
}