#include "Aurora/Renderer/Renderer2D.h"
#include "Aurora/Renderer/RendererAPI.h"

namespace Aurora
{

    RendererAPI *
        Renderer2D::s_Renderer = nullptr;

    Camera2D *
        Renderer2D::s_Camera = nullptr;

    void Renderer2D::Init(
        RendererAPI *renderer)
    {
        s_Renderer = renderer;

        s_Renderer->Init();
    }

    void Renderer2D::Shutdown()
    {
        s_Renderer = nullptr;
    }

    void Renderer2D::BeginFrame()
    {
        s_Renderer->BeginFrame();
    }

    void Renderer2D::EndFrame()
    {
        s_Renderer->EndFrame();
    }

    void Renderer2D::DrawSprite(
        const TransformComponent &transform,
        const SpriteComponent &sprite)
    {
        if (!s_Camera)
        {
            s_Renderer->DrawSprite(transform, sprite);
            return;
        }

        TransformComponent cameraTransform = transform;

        cameraTransform.WorldTransform.Position =
            s_Camera->WorldToScreen(transform.WorldTransform.Position);

        s_Renderer->DrawSprite(
            cameraTransform,
            sprite);
    }

    void Renderer2D::SetCamera(
        Camera2D *camera)
    {
        s_Camera = camera;
    }

    RendererAPI *Renderer2D::GetRendererAPI()
    {
        return s_Renderer;
    }
}