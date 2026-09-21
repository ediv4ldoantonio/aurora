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

        void InitializeScreenTextureUniform();

    private:
        bool m_Enabled = true;
        bool m_ScreenTextureUniformInitialized = false;

        RendererAPI *m_Renderer = nullptr;

        PostProcessEffect m_Effect =
            PostProcessEffect::None;

        std::shared_ptr<Shader> m_Shader;

        struct FloatUniform
        {
            float Value = 0.0f;
            bool Dirty = true;
        };

        struct IntUniform
        {
            int Value = 0;
            bool Dirty = true;
        };

        struct Vector2Uniform
        {
            Vector2 Value{};
            bool Dirty = true;
        };

        std::unordered_map<std::string, FloatUniform>
            m_FloatUniforms;

        std::unordered_map<std::string, IntUniform>
            m_IntUniforms;

        std::unordered_map<std::string, Vector2Uniform>
            m_Vector2Uniforms;
    };
}