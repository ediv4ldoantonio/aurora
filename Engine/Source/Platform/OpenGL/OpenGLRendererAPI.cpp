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

        // Test code to verify that OpenGL is working
        TestVertex vertices[3] = {
            {{-0.5f, -0.5f}},
            {{0.5f, -0.5f}},
            {{0.0f, 0.5f}}};

        auto vertexBuffer =
            RendererResourceFactory::CreateVertexBuffer(
                sizeof(vertices));

        auto indexBuffer =
            RendererResourceFactory::CreateIndexBuffer(3);

        auto vertexArray =
            RendererResourceFactory::CreateVertexArray();

        BufferLayout layout =
            {
                {ShaderDataType::Float2,
                 "a_Position"}};

        vertexBuffer->SetLayout(layout);

        vertexBuffer->SetData(
            vertices,
            sizeof(vertices));

        vertexArray->AddVertexBuffer(vertexBuffer);
        vertexArray->SetIndexBuffer(indexBuffer);

        const uint32_t indices[] =
            {
                0, 1, 2};

        indexBuffer->SetData(
            indices,
            3);

        const char *vertexSource = R"(
#version 330 core

layout(location = 0) in vec2 a_Position;

void main()
{
    gl_Position = vec4(a_Position, 0.0, 1.0);
}
)";

        const char *fragmentSource = R"(
#version 330 core

out vec4 o_Color;

void main()
{
    o_Color = vec4(1.0, 1.0, 1.0, 1.0);
}
)";

        auto shader =
            RendererResourceFactory::CreateShader(
                vertexSource,
                fragmentSource);

        shader->Bind();

        vertexArray->Bind();

        Clear(Color(20, 20, 20, 255));

        glDrawElements(
            GL_TRIANGLES,
            static_cast<GLsizei>(
                indexBuffer->GetCount()),
            GL_UNSIGNED_INT,
            nullptr);
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
}