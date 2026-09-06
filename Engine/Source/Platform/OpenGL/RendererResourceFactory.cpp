#include "Aurora/Renderer/RendererResourceFactory.h"
#include "Aurora/Renderer/RendererAPI.h"

#include "OpenGLVertexBuffer.h"
#include "OpenGLIndexBuffer.h"
#include "OpenGLVertexArray.h"
#include "OpenGLShader.h"
#include "OpenGLTexture2D.h"

#include "../SDL/SDLTexture2D.h"

#include <stdexcept>
#include <memory>

namespace Aurora
{
    RendererBackend
        RendererResourceFactory::s_Backend =
            RendererBackend::OpenGL;

    void RendererResourceFactory::Init(
        RendererBackend backend)
    {
        s_Backend = backend;
    }

    std::shared_ptr<VertexBuffer>
    RendererResourceFactory::CreateVertexBuffer(
        size_t size)
    {
        switch (s_Backend)
        {
        case RendererBackend::SDL:
            throw std::runtime_error(
                "VertexBuffer is not supported "
                "by the SDL renderer");

        case RendererBackend::OpenGL:
            return std::make_shared<OpenGLVertexBuffer>(size);

        case RendererBackend::None:
            throw std::runtime_error(
                "No renderer backend selected");
        }

        throw std::runtime_error(
            "Unknown renderer backend");
    }

    std::shared_ptr<IndexBuffer>
    RendererResourceFactory::CreateIndexBuffer(
        size_t count)
    {
        switch (s_Backend)
        {
        case RendererBackend::SDL:
            throw std::runtime_error(
                "IndexBuffer is not supported "
                "by the SDL renderer");

        case RendererBackend::OpenGL:
            return std::make_shared<OpenGLIndexBuffer>(count);

        case RendererBackend::None:
            throw std::runtime_error(
                "No renderer backend selected");
        }

        throw std::runtime_error(
            "Unknown renderer backend");
    }

    std::shared_ptr<VertexArray>
    RendererResourceFactory::CreateVertexArray()
    {
        switch (s_Backend)
        {
        case RendererBackend::SDL:
            throw std::runtime_error(
                "VertexArray is not supported "
                "by the SDL renderer");

        case RendererBackend::OpenGL:
            return std::make_shared<OpenGLVertexArray>();

        case RendererBackend::None:
            throw std::runtime_error(
                "No renderer backend selected");
        }

        throw std::runtime_error(
            "Unknown renderer backend");
    }

    std::shared_ptr<Shader>
    RendererResourceFactory::CreateShader(
        const std::string &vertexSource,
        const std::string &fragmentSource)
    {
        switch (s_Backend)
        {
        case RendererBackend::SDL:
            throw std::runtime_error(
                "SDL Shader is not implemented");

        case RendererBackend::OpenGL:
            return std::make_shared<OpenGLShader>(
                vertexSource,
                fragmentSource);
        }

        throw std::runtime_error(
            "Unsupported renderer backend");
    }

    std::shared_ptr<Texture2D>
    RendererResourceFactory::CreateTexture2D(
        const std::string &path)
    {
        switch (s_Backend)
        {
        case RendererBackend::SDL:
            return std::make_shared<SDLTexture2D>(
                path);

        case RendererBackend::OpenGL:
            return std::make_shared<OpenGLTexture2D>(
                path);
        }

        throw std::runtime_error(
            "Unsupported renderer backend");
    }
}