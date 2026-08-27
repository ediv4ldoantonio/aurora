#pragma once

#include "Aurora/Math/Vector2.h"
#include "Aurora/Renderer/Camera2D.h"
#include "Aurora/Renderer/RenderState.h"
#include "Aurora/Scene/Components/SpriteComponent.h"
#include "Aurora/Scene/Components/TransformComponent.h"
#include "Aurora/Renderer/SpriteBatch.h"
#include "Aurora/Renderer/RenderQueue.h"

#include <vector>
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

        static void Flush();

    private:
        static void FlushBatch();

        static RendererAPI *s_Renderer;
        static Camera2D *s_Camera;
        static RenderState s_RenderState;
        static SpriteBatch s_SpriteBatch;
        static RenderQueue s_RenderQueue;

        static uint32_t s_BatchCount;
        static uint32_t s_BatchBreakCount;
    };

}