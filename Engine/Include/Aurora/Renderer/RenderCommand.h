#pragma once

namespace Aurora
{

    class RenderCommand
    {
    public:
        static void Clear();

        static void SetViewport(
            int x,
            int y,
            int width,
            int height);
    };

}