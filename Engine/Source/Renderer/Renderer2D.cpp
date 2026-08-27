#include "Aurora/Renderer/Renderer2D.h"
#include "Aurora/Renderer/RendererAPI.h"
#include "Aurora/Renderer/RenderCommand.h"
#include "Aurora/Core/Logger.h"
#include "Aurora/Core/Assert.h"

#include <algorithm>

namespace Aurora
{

    RendererAPI *
        Renderer2D::s_Renderer = nullptr;

    Camera2D *
        Renderer2D::s_Camera = nullptr;

    RenderState
        Renderer2D::s_RenderState;

    SpriteBatch
        Renderer2D::s_SpriteBatch;

    RenderQueue Renderer2D::s_RenderQueue;

    uint32_t Renderer2D::s_BatchCount = 0;
    uint32_t Renderer2D::s_BatchBreakCount = 0;

    void Renderer2D::Init(
        RendererAPI *renderer)
    {
        s_Renderer = renderer;

        RenderCommand::Init(
            renderer);
    }

    void Renderer2D::Shutdown()
    {
        s_Renderer = nullptr;
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

        RenderCommand::Clear();
    }

    void Renderer2D::EndFrame()
    {
        Flush();

        if (!s_Renderer)
            return;

        s_Renderer->EndFrame();
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
            s_Camera->WorldToScreen(
                transform.WorldTransform.Position);

        command.Size =
            transform.WorldTransform.Scale;

        command.Size.x *=
            s_Camera->GetZoom();

        command.Size.y *=
            s_Camera->GetZoom();

        command.Rotation =
            transform.WorldTransform.Rotation - s_Camera->GetRotation();

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

        command.Batch.MaterialID =
            sprite.MaterialInstance->GetID();

        s_RenderQueue.Submit(
            command);
    }

    void Renderer2D::SetCamera(
        Camera2D *camera)
    {
        s_Camera = camera;

        if (!s_Camera)
            return;

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
}