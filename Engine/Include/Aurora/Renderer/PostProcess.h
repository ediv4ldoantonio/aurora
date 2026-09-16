#pragma once

#include "Aurora/Renderer/Texture2D.h"

#include <memory>

namespace Aurora
{
    class RendererAPI;

    class PostProcess
    {
    public:
        static void Init(RendererAPI *renderer);
        static void Shutdown();

        static void Apply(
            const std::shared_ptr<Texture2D> &source);

    private:
        static RendererAPI *s_Renderer;
    };
}