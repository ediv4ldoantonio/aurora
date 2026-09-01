#include "SDLGraphicsContext.h"
#include "SDLRendererAPI.h"
#include <SDL3/SDL.h>
#include <Aurora/Core/Logger.h>

namespace Aurora
{

    SDLGraphicsContext::SDLGraphicsContext(
        SDL_Window *window)
        : m_Window(window)
    {
    }

    SDLGraphicsContext::~SDLGraphicsContext()
    {

        m_RendererAPI.reset();

        if (m_Renderer)
        {
            SDL_DestroyRenderer(
                m_Renderer);
        }
    }

    void SDLGraphicsContext::Init()
    {
        RendererAPI::SetBackend(
            RendererBackend::SDL);

        m_Renderer =
            SDL_CreateRenderer(
                m_Window,
                nullptr);

        if (!m_Renderer)
        {
            AURORA_LOG_ERROR("Error creating Renderer");
        }

        m_RendererAPI =
            std::make_unique<SDLRendererAPI>(
                m_Renderer);

        m_RendererAPI->Init();
    }

    RendererAPI *
    SDLGraphicsContext::GetRendererAPI()
    {
        return m_RendererAPI.get();
    }
}