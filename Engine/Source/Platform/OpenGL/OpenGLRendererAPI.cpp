#include "OpenGLRendererAPI.h"
#include "Aurora/Renderer/RendererResourceFactory.h"
#include "Aurora/Renderer/BufferLayout.h"
#include "Aurora/Renderer/VertexBuffer.h"
#include "Aurora/Renderer/IndexBuffer.h"
#include "Aurora/Renderer/VertexArray.h"
#include "Aurora/Renderer/Shader.h"
#include "Aurora/Renderer/SpriteBatch.h"

#include <glad/gl.h>
#include <fstream>

namespace Aurora
{
    namespace
    {
        std::string LoadShaderSource(
            const std::string &path)
        {
            std::ifstream file(path);

            if (!file)
                throw std::runtime_error(
                    "Failed to open shader source: " + path);

            return std::string(
                std::istreambuf_iterator<char>(file),
                std::istreambuf_iterator<char>());
        }
    }

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

        m_SpriteVertexArray =
            RendererResourceFactory::CreateVertexArray();

        m_SpriteVertexBuffer =
            RendererResourceFactory::CreateVertexBuffer(
                sizeof(SpriteVertex) * SpriteBatch::MaxQuads * 4);

        m_SpriteIndexBuffer =
            RendererResourceFactory::CreateIndexBuffer(
                SpriteBatch::MaxQuads * 6);

        BufferLayout layout =
            {
                {ShaderDataType::Float2,
                 "a_Position"},
                {ShaderDataType::Float2,
                 "a_TexCoord"},
                {ShaderDataType::UByte4,
                 "a_Color",
                 true},
                {ShaderDataType::Float,
                 "a_MaterialIndex"}};

        m_SpriteVertexBuffer->SetLayout(layout);

        m_SpriteVertexArray->AddVertexBuffer(
            m_SpriteVertexBuffer);

        m_SpriteVertexArray->SetIndexBuffer(
            m_SpriteIndexBuffer);

        std::vector<uint32_t> indices(
            SpriteBatch::MaxQuads * 6);

        for (size_t i = 0; i < SpriteBatch::MaxQuads; ++i)
        {
            const uint32_t vertexOffset =
                static_cast<uint32_t>(i * 4);

            const size_t indexOffset = i * 6;

            indices[indexOffset + 0] =
                vertexOffset + 0;

            indices[indexOffset + 1] =
                vertexOffset + 1;

            indices[indexOffset + 2] =
                vertexOffset + 2;

            indices[indexOffset + 3] =
                vertexOffset + 2;

            indices[indexOffset + 4] =
                vertexOffset + 3;

            indices[indexOffset + 5] =
                vertexOffset + 0;
        }

        m_SpriteIndexBuffer->SetData(
            indices.data(),
            indices.size());

        const std::string vertexSource =
            LoadShaderSource("Engine/Assets/Shaders/Sprite.vert");

        const std::string fragmentSource =
            LoadShaderSource("Engine/Assets/Shaders/Sprite.frag");

        m_SpriteShader =
            RendererResourceFactory::CreateShader(
                vertexSource,
                fragmentSource);

        m_SpriteShader->Bind();

        for (int i = 0; i < 16; ++i)
        {
            m_SpriteShader->SetInt(
                "u_Textures[" +
                    std::to_string(i) +
                    "]",
                i);
        }

        m_SpriteShader->Unbind();
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
        if (batch.GetVertices().empty())
            return;

        m_SpriteShader->Bind();

        m_SpriteVertexArray->Bind();

        m_SpriteVertexBuffer->SetData(
            batch.GetVertices().data(),
            batch.GetVertices().size() *
                sizeof(SpriteVertex));

        const auto &materials =
            batch.GetMaterials();

        for (size_t i = 0;
             i < materials.size();
             ++i)
        {
            Material *material = materials[i];

            if (!material)
                continue;

            const auto &texture =
                material->GetTexture();

            if (texture)
            {
                texture->Bind(
                    static_cast<uint32_t>(i));
            }
        }

        DrawIndexed(
            m_SpriteVertexArray,
            static_cast<uint32_t>(
                batch.GetIndices().size()));
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

    void OpenGLRendererAPI::SetViewProjection(
        const Matrix4 &viewProjection)
    {
        if (!m_SpriteShader)
        {
            throw std::runtime_error(
                "Sprite shader is not initialized");
        }

        m_SpriteShader->Bind();

        m_SpriteShader->SetMatrix4(
            "u_ViewProjection",
            viewProjection.GetData());

        m_SpriteShader->Unbind();
    }
}