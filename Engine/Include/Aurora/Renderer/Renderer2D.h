#pragma once

#include "Aurora/Math/Vector2.h"
#include "Aurora/Renderer/Camera2D.h"
#include "Aurora/Renderer/RenderState.h"
#include "Aurora/Scene/Components/SpriteComponent.h"
#include "Aurora/Scene/Components/TransformComponent.h"

#include <memory>

namespace Aurora
{

    class RendererAPI;

    class Renderer2D
    {

    public:
        static void Init(
            RendererAPI *renderer);

        static void Shutdown();

        static void BeginFrame();

        static void EndFrame();

        static void DrawSprite(
            const TransformComponent &transform,
            const SpriteComponent &sprite);

        static void SetCamera(
            Camera2D *camera);

        static RendererAPI *GetRendererAPI();

    private:
        static RendererAPI *s_Renderer;
        static Camera2D *s_Camera;
        static RenderState s_RenderState;
    };

}