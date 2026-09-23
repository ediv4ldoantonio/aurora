#include "Aurora/Renderer/Renderer2D.h"
#include "Aurora/Renderer/RendererAPI.h"
#include "Aurora/Renderer/RenderCommand.h"
#include "Aurora/Renderer/RendererResourceFactory.h"
#include "Aurora/Renderer/PostProcess.h"
#include "Aurora/Core/Logger.h"
#include "Aurora/Core/Assert.h"
#include "Aurora/Core/Window.h"

#include <algorithm>
#include <stdexcept>
#include <string>

namespace Aurora
{
    RendererAPI *
        Renderer2D::s_Renderer = nullptr;

    GraphicsContext *
        Renderer2D::s_GraphicsContext = nullptr;

    Window *
        Renderer2D::s_Window = nullptr;

    Camera2D *
        Renderer2D::s_Camera = nullptr;

    RenderState
        Renderer2D::s_RenderState;

    SpriteBatch
        Renderer2D::s_SpriteBatch;

    RenderQueue Renderer2D::s_RenderQueue;

    uint32_t Renderer2D::s_BatchCount = 0;

    uint32_t Renderer2D::s_BatchBreakCount = 0;

    std::shared_ptr<Framebuffer>
        Renderer2D::s_SceneFramebuffer = nullptr;

    Matrix4 Renderer2D::s_LastViewProjectionMatrix;
    bool Renderer2D::s_HasViewProjectionMatrix = false;

    void Renderer2D::Init(Window &window)
    {
        s_Window = &window;
        auto &context = window.GetGraphicsContext();
        s_GraphicsContext = &context;
        s_Renderer = context.GetRendererAPI();

        if (!s_Renderer)
            throw std::invalid_argument(
                "Renderer2D received null RendererAPI");

        s_Renderer->Init();

        RenderCommand::Init(
            s_Renderer);

        RendererResourceFactory::Init(
            s_Renderer->GetBackend());

        PostProcess::Init(
            s_Renderer,
            window.GetWidth(),
            window.GetHeight());

        FramebufferSpecification specification;

        specification.Width = window.GetWidth();
        specification.Height = window.GetHeight();
        specification.HasDepthStencil = true;

        s_SceneFramebuffer =
            RendererResourceFactory::CreateFramebuffer(
                specification);
    }

    void Renderer2D::Shutdown()
    {
        PostProcess::Shutdown();

        s_SpriteBatch.Clear();
        s_RenderQueue.Clear();

        s_SceneFramebuffer.reset();

        s_Camera = nullptr;
        s_Renderer = nullptr;
        s_GraphicsContext = nullptr;
        s_Window = nullptr;

        s_HasViewProjectionMatrix = false;
    }

    void Renderer2D::BeginFrame()
    {
        if (!s_Renderer)
            return;

        s_BatchCount = 0;
        s_BatchBreakCount = 0;

        s_RenderQueue.Clear();
        s_SpriteBatch.Clear();

        s_Renderer->BeginFrame();

        if (s_SceneFramebuffer)
        {
            s_SceneFramebuffer->Bind();

            RenderCommand::SetViewport(
                0,
                0,
                static_cast<int>(
                    s_SceneFramebuffer->GetWidth()),
                static_cast<int>(
                    s_SceneFramebuffer->GetHeight()));
        }

        RenderCommand::Clear();

        if (s_Camera && s_Renderer)
        {
            const Matrix4 viewProjection =
                s_Camera->GetViewProjectionMatrix();

            const bool changed =
                !s_HasViewProjectionMatrix ||
                std::memcmp(
                    viewProjection.GetData(),
                    s_LastViewProjectionMatrix.GetData(),
                    sizeof(float) * 16) != 0;

            if (changed)
            {
                s_Renderer->SetViewProjection(
                    viewProjection);

                s_LastViewProjectionMatrix =
                    viewProjection;

                s_HasViewProjectionMatrix = true;
            }
        }
    }

    void Renderer2D::EndFrame()
    {
        Flush();

        if (!s_Renderer)
            return;

        if (s_SceneFramebuffer)
        {
            s_SceneFramebuffer->Unbind();

            s_Renderer->SetViewport(
                0,
                0,
                s_Window->GetWidth(),
                s_Window->GetHeight());

            RenderCommand::SetViewport(
                0,
                0,
                static_cast<int>(
                    s_SceneFramebuffer->GetWidth()),
                static_cast<int>(
                    s_SceneFramebuffer->GetHeight()));

            PostProcess::Apply(
                s_SceneFramebuffer->GetColorAttachment());
        }

        s_Renderer->EndFrame();

        s_GraphicsContext->SwapBuffers();
    }

    void Renderer2D::DrawSprite(
        const TransformComponent &transform,
        const SpriteComponent &sprite)
    {
        if (!s_Renderer)
            return;

        if (!s_Camera)
            return;

        SpriteDrawCommand command;

        command.Position =
            transform.WorldTransform.Position;

        command.Size =
            transform.WorldTransform.Scale;

        command.Rotation =
            transform.WorldTransform.Rotation;

        if (!sprite.MaterialInstance)
        {
            AURORA_LOG_WARN(
                "SpriteComponent has no MaterialInstance. Skipping draw call.");
            return;
        }

        command.MaterialInstance =
            sprite.MaterialInstance.get();

        command.SortKey.Pass =
            sprite.Pass;

        command.SortKey.Layer =
            sprite.Layer;

        command.Batch.Pass =
            sprite.Pass;

        command.Batch.BlendMode =
            sprite.MaterialInstance->GetBlendMode();

        s_RenderQueue.Submit(
            command);
    }

    void Renderer2D::SetCamera(
        Camera2D *camera)
    {
        s_Camera = camera;

        s_HasViewProjectionMatrix = false;

        if (!s_Camera)
            return;

        if (s_Window)
        {
            s_Camera->SetViewportSize(
                {static_cast<float>(s_Window->GetWidth()),
                 static_cast<float>(s_Window->GetHeight())});
        }

        s_RenderState.ViewMatrix =
            s_Camera->GetViewMatrix();

        s_RenderState.ProjectionMatrix =
            s_Camera->GetProjectionMatrix();
    }

    RendererAPI *Renderer2D::GetRendererAPI()
    {
        return s_Renderer;
    }

    void Renderer2D::Flush()
    {
        if (!s_Renderer)
            return;

        s_RenderQueue.Sort();

        s_RenderQueue.OptimizeForBatching();

        const auto &commands =
            s_RenderQueue.GetCommands();

        for (const auto &command :
             commands)
        {
            if (!s_SpriteBatch.CanBatchWith(
                    command.Batch))
            {
                ++s_BatchBreakCount;

                FlushBatch();
            }

            if (!s_SpriteBatch.CanAdd(
                    command.MaterialInstance))
            {

                ++s_BatchBreakCount;

                FlushBatch();
            }

            s_SpriteBatch.AddQuad(
                command.Position,
                command.Size,
                command.Rotation,
                command.MaterialInstance,
                command.Batch);
        }

        FlushBatch();

        s_RenderQueue.Clear();
    }

    void Renderer2D::FlushBatch()
    {
        if (!s_Renderer)
            return;

        if (s_SpriteBatch.GetVertices().empty())
            return;

        ++s_BatchCount;

        s_Renderer->DrawSpriteBatch(
            s_SpriteBatch);

        s_SpriteBatch.Clear();
    }

    void Renderer2D::OnResize(
        uint32_t width,
        uint32_t height)
    {
        if (!s_Renderer)
            return;

        if (width == 0 || height == 0)
            return;

        if (s_SceneFramebuffer)
        {
            s_SceneFramebuffer->Resize(
                width,
                height);
        }

        PostProcess::Resize(
            width,
            height);

        RenderCommand::SetViewport(
            0,
            0,
            width,
            height);

        if (s_Camera)
        {
            s_Camera->SetViewportSize(
                {static_cast<float>(width),
                 static_cast<float>(height)});
        }
    }
}