#pragma once

#include "Aurora/Math/Vector2.h"
#include "Aurora/Renderer/Camera2D.h"
#include "Aurora/Renderer/RenderState.h"
#include "Aurora/Renderer/RenderQueue.h"
#include "Aurora/Renderer/SpriteBatch.h"
#include "Aurora/Renderer/Shader.h"
#include "Aurora/Renderer/GraphicsContext.h"
#include "Aurora/Renderer/Framebuffer.h"
#include "Aurora/Scene/Components/SpriteComponent.h"
#include "Aurora/Scene/Components/TransformComponent.h"

#include <vector>
#include <memory>
#include <cstring>

namespace Aurora
{

    class Window;
    class RendererAPI;

    class Renderer2D
    {

    public:
        static void Init(Window &window);

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

        static void OnResize(
            uint32_t width,
            uint32_t height);

        struct Statistics
        {
            uint32_t SpriteCount = 0;
            uint32_t SpriteDrawCalls = 0;
            uint32_t BatchCount = 0;
            uint32_t BatchBreakCount = 0;
            uint32_t VertexCount = 0;
            uint32_t IndexCount = 0;
        };

        static const Statistics &GetStatistics();

        static float GetAverageSpritesPerDrawCall();

    private:
        static void FlushBatch();

        static Matrix4 s_LastViewProjectionMatrix;
        static bool s_HasViewProjectionMatrix;

        static RendererAPI *s_Renderer;
        static GraphicsContext *s_GraphicsContext;
        static Window *s_Window;
        static Camera2D *s_Camera;

        static RenderState s_RenderState;
        static SpriteBatch s_SpriteBatch;
        static RenderQueue s_RenderQueue;

        static std::shared_ptr<Framebuffer> s_SceneFramebuffer;

        static Statistics s_Statistics;
    };

}