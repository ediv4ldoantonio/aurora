#include "Aurora/Renderer/VertexBuffer.h"
#include "Aurora/Renderer/RendererAPI.h"

#include <stdexcept>

namespace Aurora
{
    std::shared_ptr<VertexBuffer>
    VertexBuffer::Create(size_t size)
    {
        switch (RendererAPI::GetBackend())
        {
        case RendererBackend::SDL:
            break;

        case RendererBackend::OpenGL:
            // OpenGL implementation
            break;

        case RendererBackend::None:
            break;
        }

        throw std::runtime_error(
            "Unsupported renderer backend");
    }
}