#pragma once

#include "Aurora/Renderer/RendererBackend.h"
#include "Aurora/Renderer/Shader.h"
#include "Aurora/Renderer/Texture2D.h"

#include <cstddef>
#include <memory>

namespace Aurora
{
    class VertexBuffer;
    class IndexBuffer;
    class VertexArray;

    class RendererResourceFactory
    {
    public:
        static void Init(
            RendererBackend backend);

        static std::shared_ptr<VertexBuffer>
        CreateVertexBuffer(
            size_t size);

        static std::shared_ptr<IndexBuffer>
        CreateIndexBuffer(
            size_t count);

        static std::shared_ptr<VertexArray>
        CreateVertexArray();

        static std::shared_ptr<Shader>
        CreateShader(
            const std::string &vertexSource,
            const std::string &fragmentSource);

        static std::shared_ptr<Texture2D>
        CreateTexture2D(const std::string &path);

    private:
        static RendererBackend s_Backend;
    };
}