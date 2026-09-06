#include "OpenGLRendererAPI.h"
#include "Aurora/Renderer/RendererResourceFactory.h"
#include "Aurora/Renderer/BufferLayout.h"
#include "Aurora/Renderer/VertexBuffer.h"
#include "Aurora/Renderer/IndexBuffer.h"
#include "Aurora/Renderer/VertexArray.h"
#include "Aurora/Renderer/Shader.h"
#include <glad/gl.h>

namespace Aurora
{
    struct TestVertex
    {
        float Position[2];
    };

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

    void OpenGLRendererAPI::DrawIndexed(
        const std::shared_ptr<VertexArray> &vertexArray,
        uint32_t indexCount)
    {
        if (!vertexArray)
        {
            throw std::invalid_argument(
                "DrawIndexed received null VertexArray");
        }

        vertexArray->Bind();

        glDrawElements(
            GL_TRIANGLES,
            static_cast<GLsizei>(indexCount),
            GL_UNSIGNED_INT,
            nullptr);
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

    void OpenGLRendererAPI::Clear(const Color &color)
    {
        glClearColor(
            color.R / 255.0f,
            color.G / 255.0f,
            color.B / 255.0f,
            color.A / 255.0f);

        glClear(GL_COLOR_BUFFER_BIT);
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

    void OpenGLRendererAPI::ApplyMaterial(
        const Material &material,
        const std::shared_ptr<Shader> &shader)
    {
        }
}