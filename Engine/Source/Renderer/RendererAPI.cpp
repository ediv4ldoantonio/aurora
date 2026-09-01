#include "Aurora/Renderer/RendererAPI.h"

namespace Aurora
{

    RendererBackend RendererAPI::s_Backend = RendererBackend::SDL;

    RendererBackend RendererAPI::GetBackend()
    {
        return s_Backend;
    }

    void RendererAPI::SetBackend(
        RendererBackend backend)
    {
        s_Backend = backend;
    }

}