#pragma once

#include "Aurora/Renderer/Framebuffer.h"
#include "Aurora/Renderer/Shader.h"
#include "Aurora/Renderer/Texture2D.h"
#include "Aurora/Renderer/PostProcessEffect.h"

#include <memory>

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

        void Apply(
            const std::shared_ptr<Texture2D> &source,
            const std::shared_ptr<Framebuffer> &target);

    private:
        RendererAPI *m_Renderer = nullptr;

        PostProcessEffect m_Effect =
            PostProcessEffect::None;

        std::shared_ptr<Shader> m_Shader;
    };
}