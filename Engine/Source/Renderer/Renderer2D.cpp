#include "Aurora/Renderer/Renderer2D.h"
#include "Aurora/Renderer/RendererAPI.h"
#include "Aurora/Renderer/RenderCommand.h"

namespace Aurora
{

    RendererAPI *
        Renderer2D::s_Renderer = nullptr;

    Camera2D *
        Renderer2D::s_Camera = nullptr;

    RenderState
        Renderer2D::s_RenderState;

    std::vector<SpriteDrawCommand>
        Renderer2D::s_SpriteCommands;

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

        s_Renderer->BeginFrame();

        RenderCommand::Clear();

        s_SpriteCommands.clear();
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

        command.Tint =
            sprite.Tint;

        command.Texture =
            sprite.Texture.get();

        s_SpriteCommands.push_back(
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

        for (const auto &command :
             s_SpriteCommands)
        {
            s_Renderer->DrawSprite(
                command);
        }

        s_SpriteCommands.clear();
    }
}