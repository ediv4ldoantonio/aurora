#include "Aurora/Renderer/RendererResourceFactory.h"

#include "Aurora/Renderer/RendererAPI.h"

#include <stdexcept>

namespace Aurora
{
    std::shared_ptr<VertexBuffer>
    RendererResourceFactory::CreateVertexBuffer(
        size_t size)
    {
        switch (RendererAPI::GetBackend())
        {
        case RendererBackend::SDL:
            throw std::runtime_error(
                "VertexBuffer is not supported "
                "by the SDL renderer");

        case RendererBackend::OpenGL:
            throw std::runtime_error(
                "OpenGLVertexBuffer is not "
                "implemented yet");

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
        switch (RendererAPI::GetBackend())
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
        switch (RendererAPI::GetBackend())
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