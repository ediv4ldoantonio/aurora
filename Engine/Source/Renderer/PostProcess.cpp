#include "Aurora/Renderer/PostProcess.h"
#include "Aurora/Renderer/RendererAPI.h"

#include <stdexcept>

namespace Aurora
{
    RendererAPI *PostProcess::s_Renderer = nullptr;

    void PostProcess::Init(RendererAPI *renderer)
    {
        if (!renderer)
        {
            throw std::invalid_argument(
                "PostProcess received null RendererAPI");
        }

        s_Renderer = renderer;
    }

    void PostProcess::Shutdown()
    {
        s_Renderer = nullptr;
    }

    void PostProcess::Apply(
        const std::shared_ptr<Texture2D> &source)
    {
        if (!s_Renderer)
            return;

        if (!source)
            return;

        s_Renderer->DrawFramebuffer(source);
    }
}