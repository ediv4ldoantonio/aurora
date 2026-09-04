#pragma once

#include "Aurora/Renderer/GraphicsContext.h"
#include "OpenGLRendererAPI.h"

struct SDL_GLContextState;
struct SDL_Window;
using SDL_GLContext = SDL_GLContextState *;

namespace Aurora
{
    class RendererAPI;

    class OpenGLGraphicsContext
        : public GraphicsContext
    {
    public:
        explicit OpenGLGraphicsContext(
            SDL_Window *window);

        ~OpenGLGraphicsContext() override;

        void Init() override;

        RendererAPI *
        GetRendererAPI() override;

        void SwapBuffers() override;

    private:
        SDL_Window *m_Window = nullptr;

        SDL_GLContext m_Context = nullptr;

        std::unique_ptr<OpenGLRendererAPI>
            m_RendererAPI;
    };
}