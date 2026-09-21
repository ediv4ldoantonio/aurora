#include "Aurora/Renderer/PostProcess.h"
#include "Aurora/Renderer/RendererAPI.h"
#include "Aurora/Renderer/RendererResourceFactory.h"

#include <stdexcept>
#include <fstream>

namespace Aurora
{
    namespace
    {
        std::string LoadShaderSource(
            const std::string &path)
        {
            std::ifstream file(path);

            if (!file)
                throw std::runtime_error(
                    "Failed to open shader source: " + path);

            return std::string(
                std::istreambuf_iterator<char>(file),
                std::istreambuf_iterator<char>());
        }
    }

    RendererAPI *PostProcess::s_Renderer = nullptr;

    PostProcessEffect PostProcess::s_Effect =
        PostProcessEffect::None;

    std::shared_ptr<Framebuffer>
        PostProcess::s_PingFramebuffer = nullptr;

    std::shared_ptr<Framebuffer>
        PostProcess::s_PongFramebuffer = nullptr;

    std::vector<PostProcessEffect>
        PostProcess::s_Effects;

    std::unordered_map<
        PostProcessEffect,
        PostProcessPass>
        PostProcess::s_Passes;

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

        s_Passes.clear();

        InitShaders();
    }

    void PostProcess::InitShaders()
    {
        const std::string fullscreenVertexSource =
            LoadShaderSource("Engine/Assets/Shaders/Screen.vert");

        const std::string grayscaleFragmentSource =
            LoadShaderSource("Engine/Assets/Shaders/Grayscale.frag");

        const std::string invertFragmentSource =
            LoadShaderSource("Engine/Assets/Shaders/Invert.frag");

        const std::string vignetteFragmentSource =
            LoadShaderSource("Engine/Assets/Shaders/Vignette.frag");

        auto grayscaleShader =
            RendererResourceFactory::CreateShader(
                fullscreenVertexSource,
                grayscaleFragmentSource);

        auto invertShader =
            RendererResourceFactory::CreateShader(
                fullscreenVertexSource,
                invertFragmentSource);

        auto vignetteShader =
            RendererResourceFactory::CreateShader(
                fullscreenVertexSource,
                vignetteFragmentSource);

        grayscaleShader->Bind();
        grayscaleShader->SetInt(
            "u_ScreenTexture",
            0);
        grayscaleShader->Unbind();

        invertShader->Bind();
        invertShader->SetInt(
            "u_ScreenTexture",
            0);
        invertShader->Unbind();

        vignetteShader->Bind();
        vignetteShader->SetInt(
            "u_ScreenTexture",
            0);
        vignetteShader->Unbind();

        s_Passes.emplace(
            PostProcessEffect::Grayscale,
            PostProcessPass(
                s_Renderer,
                PostProcessEffect::Grayscale,
                std::move(grayscaleShader)));

        s_Passes.emplace(
            PostProcessEffect::Invert,
            PostProcessPass(
                s_Renderer,
                PostProcessEffect::Invert,
                std::move(invertShader)));

        s_Passes.emplace(
            PostProcessEffect::Vignette,
            PostProcessPass(
                s_Renderer,
                PostProcessEffect::Vignette,
                std::move(vignetteShader)));

        auto *vignettePass =
            FindPass(
                PostProcessEffect::Vignette);

        if (vignettePass)
        {
            vignettePass->SetFloat(
                "u_Strength",
                0.75f);
        }
    }

    void PostProcess::Shutdown()
    {
        s_Passes.clear();

        s_PingFramebuffer.reset();
        s_PongFramebuffer.reset();

        s_Renderer = nullptr;

        s_Effect =
            PostProcessEffect::None;

        s_Effects.clear();
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

            auto *pass =
                FindPass(effect);

            if (!pass)
                continue;

            const auto &target =
                ping
                    ? s_PingFramebuffer
                    : s_PongFramebuffer;

            pass->Apply(
                currentSource,
                target);

            currentSource =
                target->GetColorAttachment();

            ping = !ping;
        }

        s_Renderer->DrawFramebuffer(
            currentSource);
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

    PostProcessPass *
    PostProcess::FindPass(
        PostProcessEffect effect)
    {
        auto it =
            s_Passes.find(effect);

        if (it == s_Passes.end())
            return nullptr;

        return &it->second;
    }
}