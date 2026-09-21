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

        static uint32_t s_BatchCount;
        static uint32_t s_BatchBreakCount;

        static std::shared_ptr<Framebuffer> s_SceneFramebuffer;
    };

}