#pragma once

#include "Aurora/Renderer/RendererBackend.h"

#include <memory>

namespace Aurora
{

    class RendererAPI;

    class GraphicsContext
    {

    public:
        virtual ~GraphicsContext() = default;

        virtual void Init() = 0;

        virtual RendererAPI *
        GetRendererAPI() = 0;

        virtual void SwapBuffers() = 0;

        static std::unique_ptr<GraphicsContext> Create(void *nativeWindow,
                                                       RendererBackend backend);
    };

}