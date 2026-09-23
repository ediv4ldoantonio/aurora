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
        constexpr uint32_t FirstMaterialTextureSlot = 1;

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
        glDisable(GL_BLEND);

        m_State = {};

        CreateSpriteResources();
        CreateScreenResources();
        CreateSpriteShader();
        CreateScreenShader();
        InvalidateShaderState();
    }

    void OpenGLRendererAPI::CreateSpriteResources()
    {
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

        std::vector<uint32_t> spriteIndices(
            SpriteBatch::MaxQuads * 6);

        for (size_t i = 0; i < SpriteBatch::MaxQuads; ++i)
        {
            const uint32_t vertexOffset =
                static_cast<uint32_t>(i * 4);

            const size_t indexOffset = i * 6;

            spriteIndices[indexOffset + 0] =
                vertexOffset + 0;

            spriteIndices[indexOffset + 1] =
                vertexOffset + 1;

            spriteIndices[indexOffset + 2] =
                vertexOffset + 2;

            spriteIndices[indexOffset + 3] =
                vertexOffset + 2;

            spriteIndices[indexOffset + 4] =
                vertexOffset + 3;

            spriteIndices[indexOffset + 5] =
                vertexOffset + 0;
        }

        m_SpriteIndexBuffer->SetData(
            spriteIndices.data(),
            spriteIndices.size());
    }

    void OpenGLRendererAPI::CreateScreenResources()
    {
        m_ScreenVertexArray =
            RendererResourceFactory::CreateVertexArray();

        m_ScreenVertexBuffer =
            RendererResourceFactory::CreateVertexBuffer(
                4 * sizeof(float) * 4);

        m_ScreenIndexBuffer =
            RendererResourceFactory::CreateIndexBuffer(6);

        BufferLayout screenLayout =
            {
                {ShaderDataType::Float2,
                 "a_Position"},
                {ShaderDataType::Float2,
                 "a_TexCoord"}};

        m_ScreenVertexBuffer->SetLayout(
            screenLayout);

        m_ScreenVertexArray->AddVertexBuffer(
            m_ScreenVertexBuffer);

        m_ScreenVertexArray->SetIndexBuffer(
            m_ScreenIndexBuffer);

        struct ScreenVertex
        {
            float Position[2];
            float TexCoord[2];
        };

        const ScreenVertex vertices[] =
            {
                {{-1.0f, -1.0f}, {0.0f, 0.0f}},
                {{1.0f, -1.0f}, {1.0f, 0.0f}},
                {{1.0f, 1.0f}, {1.0f, 1.0f}},
                {{-1.0f, 1.0f}, {0.0f, 1.0f}}};

        m_ScreenVertexBuffer->SetData(
            vertices,
            sizeof(vertices));

        const uint32_t indices[] =
            {
                0, 1, 2,
                2, 3, 0};

        m_ScreenIndexBuffer->SetData(
            indices,
            6);
    }

    void OpenGLRendererAPI::CreateSpriteShader()
    {
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

            m_SpriteShader->SetVector4(
                "u_MaterialTints[" +
                    std::to_string(i) +
                    "]",
                1.0f,
                1.0f,
                1.0f,
                1.0f);
        }

        m_SpriteShader->Unbind();
        InvalidateShaderState();
    }

    void OpenGLRendererAPI::CreateScreenShader()
    {
        const std::string vertexSource =
            LoadShaderSource("Engine/Assets/Shaders/Screen.vert");

        const std::string fragmentSource =
            LoadShaderSource("Engine/Assets/Shaders/Screen.frag");

        m_ScreenShader =
            RendererResourceFactory::CreateShader(
                vertexSource,
                fragmentSource);

        BindShader(m_ScreenShader);

        m_ScreenShader->SetInt(
            "u_ScreenTexture",
            0);

        m_ScreenShader->Unbind();
        InvalidateShaderState();
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

        BindVertexArray(vertexArray);

        glDrawElements(
            GL_TRIANGLES,
            static_cast<GLsizei>(indexCount),
            GL_UNSIGNED_INT,
            nullptr);
    }

    void OpenGLRendererAPI::Shutdown()
    {
        m_State = {};

        m_SpriteShader.reset();
        m_SpriteVertexArray.reset();
        m_SpriteVertexBuffer.reset();
        m_SpriteIndexBuffer.reset();
        m_ScreenShader.reset();
        m_ScreenVertexArray.reset();
        m_ScreenVertexBuffer.reset();
        m_ScreenIndexBuffer.reset();
    }

    void OpenGLRendererAPI::BeginFrame()
    {
    }

    void OpenGLRendererAPI::EndFrame()
    {
    }

    void OpenGLRendererAPI::Clear(
        const Color &color)
    {
        const float red =
            color.R / 255.0f;

        const float green =
            color.G / 255.0f;

        const float blue =
            color.B / 255.0f;

        const float alpha =
            color.A / 255.0f;

        const bool colorChanged =
            !m_State.HasClearColor ||
            m_State.ClearColorR != red ||
            m_State.ClearColorG != green ||
            m_State.ClearColorB != blue ||
            m_State.ClearColorA != alpha;

        if (colorChanged)
        {
            glClearColor(
                red,
                green,
                blue,
                alpha);

            m_State.ClearColorR = red;
            m_State.ClearColorG = green;
            m_State.ClearColorB = blue;
            m_State.ClearColorA = alpha;

            m_State.HasClearColor = true;
        }

        glClear(
            GL_COLOR_BUFFER_BIT);
    }

    void OpenGLRendererAPI::SetViewport(
        int x,
        int y,
        int width,
        int height)
    {
        if (m_State.HasViewport &&
            m_State.ViewportX == x &&
            m_State.ViewportY == y &&
            m_State.ViewportWidth == width &&
            m_State.ViewportHeight == height)
        {
            return;
        }

        glViewport(
            x,
            y,
            width,
            height);

        m_State.ViewportX = x;
        m_State.ViewportY = y;
        m_State.ViewportWidth = width;
        m_State.ViewportHeight = height;
        m_State.HasViewport = true;
    }

    void OpenGLRendererAPI::DrawSprite(
        const SpriteDrawCommand &command)
    {
        (void)command;
    }

    void OpenGLRendererAPI::DrawSpriteBatch(
        const SpriteBatch &batch)
    {
        if (batch.GetVertexCount() == 0)
            return;

        UploadBatchVertices(batch);

        BindShader(m_SpriteShader);

        BindBatchMaterials(batch);

        ApplyBlendMode(
            batch.GetBlendMode());

        BindVertexArray(m_SpriteVertexArray);

        glDrawElements(
            GL_TRIANGLES,
            static_cast<GLsizei>(
                batch.GetIndexCount()),
            GL_UNSIGNED_INT,
            nullptr);
    }

    RendererBackend OpenGLRendererAPI::GetBackend() const
    {
        return RendererBackend::OpenGL;
    }

    void *OpenGLRendererAPI::GetNativeRenderer()
    {
        return nullptr;
    }

    void OpenGLRendererAPI::SetViewProjection(
        const Matrix4 &viewProjection)
    {
        if (!m_SpriteShader)
        {
            throw std::runtime_error(
                "Sprite shader is not initialized");
        }

        BindShader(m_SpriteShader);

        m_SpriteShader->SetMatrix4(
            "u_ViewProjection",
            viewProjection.GetData());
    }

    void OpenGLRendererAPI::BindBatchMaterials(
        const SpriteBatch &batch)
    {
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
                BindTexture(
                    static_cast<uint32_t>(i) +
                        FirstMaterialTextureSlot,
                    texture);
            }
        }
    }

    void OpenGLRendererAPI::UploadBatchVertices(
        const SpriteBatch &batch)
    {
        const auto &vertices =
            batch.GetVertices();

        if (vertices.empty())
            return;

        m_SpriteVertexBuffer->SetData(
            vertices.data(),
            vertices.size() * sizeof(SpriteVertex));
    }

    void OpenGLRendererAPI::ApplyBlendMode(
        BlendMode mode)
    {
        if (m_State.HasBlendMode &&
            m_State.CurrentBlendMode == mode)
        {
            return;
        }

        switch (mode)
        {
        case BlendMode::Opaque:
            glDisable(GL_BLEND);
            break;

        case BlendMode::Alpha:
            glEnable(GL_BLEND);
            glBlendFunc(
                GL_SRC_ALPHA,
                GL_ONE_MINUS_SRC_ALPHA);
            break;

        case BlendMode::Additive:
            glEnable(GL_BLEND);
            glBlendFunc(
                GL_SRC_ALPHA,
                GL_ONE);
            break;

        case BlendMode::Multiply:
            glEnable(GL_BLEND);
            glBlendFunc(
                GL_DST_COLOR,
                GL_ZERO);
            break;
        }

        m_State.CurrentBlendMode = mode;
        m_State.HasBlendMode = true;
    }

    void OpenGLRendererAPI::BindShader(
        const std::shared_ptr<Shader> &shader)
    {
        if (!shader)
            return;

        if (m_State.CurrentShader == shader.get())
            return;

        shader->Bind();

        m_State.CurrentShader = shader.get();
    }

    void OpenGLRendererAPI::InvalidateShaderState()
    {
        m_State.CurrentShader = nullptr;
    }

    void OpenGLRendererAPI::BindTexture(
        uint32_t slot,
        const std::shared_ptr<Texture2D> &texture)
    {
        if (!texture)
            return;

        if (slot >= m_State.TextureBindings.size())
            throw std::out_of_range(
                "OpenGL texture slot out of range");

        if (m_State.TextureBindings[slot] == texture)
            return;

        texture->Bind(slot);

        m_State.TextureBindings[slot] = texture;
    }

    void OpenGLRendererAPI::BindVertexArray(
        const std::shared_ptr<VertexArray> &vertexArray)
    {
        if (!vertexArray)
            return;

        if (m_State.CurrentVertexArray ==
            vertexArray.get())
        {
            return;
        }

        vertexArray->Bind();

        m_State.CurrentVertexArray =
            vertexArray.get();
    }

    void OpenGLRendererAPI::UnbindVertexArray(
        const std::shared_ptr<VertexArray> &vertexArray)
    {
        if (!vertexArray)
            return;

        if (m_State.CurrentVertexArray !=
            vertexArray.get())
        {
            return;
        }

        vertexArray->Unbind();

        m_State.CurrentVertexArray = nullptr;
    }

    void OpenGLRendererAPI::DrawFramebuffer(
        const std::shared_ptr<Texture2D> &texture)
    {
        if (!texture)
            return;

        BindShader(m_ScreenShader);

        BindTexture(
            0,
            texture);

        BindVertexArray(
            m_ScreenVertexArray);

        glDrawElements(
            GL_TRIANGLES,
            6,
            GL_UNSIGNED_INT,
            nullptr);
    }

    void OpenGLRendererAPI::DrawFramebuffer(
        const std::shared_ptr<Texture2D> &texture,
        const std::shared_ptr<Framebuffer> &target)
    {
        if (!texture)
            return;

        if (!target)
            return;

        target->Bind();

        SetViewport(
            0,
            0,
            static_cast<int>(
                target->GetWidth()),
            static_cast<int>(
                target->GetHeight()));

        BindShader(m_ScreenShader);

        BindTexture(
            0,
            texture);

        BindVertexArray(
            m_ScreenVertexArray);

        glDrawElements(
            GL_TRIANGLES,
            6,
            GL_UNSIGNED_INT,
            nullptr);

        UnbindVertexArray(
            m_ScreenVertexArray);

        target->Unbind();
    }

    void OpenGLRendererAPI::DrawPostProcess(
        const std::shared_ptr<Texture2D> &source,
        const std::shared_ptr<Framebuffer> &target,
        const std::shared_ptr<Shader> &shader)
    {
        if (!source)
            return;

        if (!target)
            return;

        if (!shader)
            return;

        target->Bind();

        SetViewport(
            0,
            0,
            static_cast<int>(
                target->GetWidth()),
            static_cast<int>(
                target->GetHeight()));

        BindShader(shader);

        BindTexture(0, source);

        BindVertexArray(
            m_ScreenVertexArray);

        glDrawElements(
            GL_TRIANGLES,
            6,
            GL_UNSIGNED_INT,
            nullptr);

        UnbindVertexArray(
            m_ScreenVertexArray);

        target->Unbind();
    }
}