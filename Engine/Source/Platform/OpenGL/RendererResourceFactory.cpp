#include "Aurora/Renderer/RendererResourceFactory.h"
#include "Aurora/Renderer/RendererAPI.h"

#include "OpenGLVertexBuffer.h"

#include <stdexcept>
#include <memory>

namespace Aurora
{
    RendererBackend
        RendererResourceFactory::s_Backend =
            RendererBackend::SDL;

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
            throw std::runtime_error(
                "OpenGLIndexBuffer is not "
                "implemented yet");

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
            throw std::runtime_error(
                "OpenGLVertexArray is not "
                "implemented yet");

        case RendererBackend::None:
            throw std::runtime_error(
                "No renderer backend selected");
        }

        throw std::runtime_error(
            "Unknown renderer backend");
    }
}