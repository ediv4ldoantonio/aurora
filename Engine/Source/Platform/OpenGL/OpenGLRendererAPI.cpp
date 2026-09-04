#include "OpenGLRendererAPI.h"

#include <glad/gl.h>

namespace Aurora
{
    void OpenGLRendererAPI::Init()
    {
        glEnable(GL_BLEND);

        glBlendFunc(
            GL_SRC_ALPHA,
            GL_ONE_MINUS_SRC_ALPHA);

        glClearColor(
            0.1f,
            0.1f,
            0.1f,
            1.0f);
    }

    void OpenGLRendererAPI::Shutdown()
    {
    }

    void OpenGLRendererAPI::BeginFrame()
    {
    }

    void OpenGLRendererAPI::EndFrame()
    {
    }

    void OpenGLRendererAPI::Clear()
    {
        glClear(
            GL_COLOR_BUFFER_BIT |
            GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRendererAPI::SetViewport(
        int x,
        int y,
        int width,
        int height)
    {
        glViewport(
            x,
            y,
            width,
            height);
    }

    void OpenGLRendererAPI::DrawSprite(
        const SpriteDrawCommand &command)
    {
        (void)command;
    }

    void OpenGLRendererAPI::DrawSpriteBatch(
        const SpriteBatch &batch)
    {
        (void)batch;
    }

    RendererBackend OpenGLRendererAPI::GetBackend() const
    {
        return RendererBackend::OpenGL;
    }

    void *OpenGLRendererAPI::GetNativeRenderer()
    {
        return nullptr;
    }
}