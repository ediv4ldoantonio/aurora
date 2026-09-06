#include "Aurora/Renderer/RenderCommand.h"
#include "Aurora/Renderer/RendererAPI.h"

namespace Aurora
{

    RendererAPI *
        RenderCommand::s_Renderer = nullptr;

    void RenderCommand::Init(
        RendererAPI *renderer)
    {
        s_Renderer = renderer;
    }

    void RenderCommand::Clear()
    {
        if (!s_Renderer)
            return;

        s_Renderer->Clear(Color(20, 20, 20, 255));
    }

    void RenderCommand::SetViewport(
        int x,
        int y,
        int width,
        int height)
    {
        if (!s_Renderer)
            return;

        s_Renderer->SetViewport(
            x,
            y,
            width,
            height);
    }

}