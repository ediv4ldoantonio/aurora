#pragma once

namespace Aurora
{
    class RendererAPI;

    class RenderCommand
    {
    public:
        static void Init(
            RendererAPI *renderer);

        static void Clear();

        static void SetViewport(
            int x,
            int y,
            int width,
            int height);

    private:
        static RendererAPI *s_Renderer;
    };
}