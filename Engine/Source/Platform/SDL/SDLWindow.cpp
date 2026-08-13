#include "SDLWindow.h"
#include "SDLGraphicsContext.h"
#include "Aurora/Events/ApplicationEvents.h"

#include <Aurora/Input/Input.h>
#include <Aurora/Core/Logger.h>
#include "Aurora/Events/KeyEvents.h"
#include "SDLKeyCodes.h"

#include <SDL3/SDL.h>

namespace Aurora
{
    SDLWindow::SDLWindow(const WindowSpecification &specification)
        : m_Specification(specification)
    {
        AURORA_LOG_INFO("Initializing SDL video subsystem");
        SDL_Init(SDL_INIT_VIDEO);

        m_Window = SDL_CreateWindow(
            m_Specification.Title.c_str(),
            m_Specification.Width,
            m_Specification.Height,
            SDL_WINDOW_RESIZABLE);

        if (!m_Window)
        {
            AURORA_LOG_ERROR("Failed to create window: ", m_Specification.Title);
        }

        m_Context = std::make_unique<SDLGraphicsContext>(m_Window);
        m_Context->Init();
    }

    SDLWindow::~SDLWindow()
    {
        m_Context.reset();

        if (m_Window)
        {
            SDL_DestroyWindow(m_Window);
        }

        SDL_Quit();
    }

    GraphicsContext &SDLWindow::GetGraphicsContext()
    {
        return *m_Context;
    }

    void SDLWindow::OnUpdate()
    {

        SDL_Event sdlEvent;

        while (SDL_PollEvent(&sdlEvent))
        {
            switch (sdlEvent.type)
            {
            case SDL_EVENT_QUIT:
            {
                WindowCloseEvent e;

                m_Specification.EventCallback(e);
            }

            case SDL_EVENT_KEY_DOWN:
            {
                KeyPressedEvent keyEvent(
                    SDLKeyToAurora(
                        sdlEvent.key.key));

                m_Specification.EventCallback(
                    keyEvent);

                break;
            }

            case SDL_EVENT_KEY_UP:
            {

                KeyReleasedEvent keyEvent(
                    SDLKeyToAurora(
                        sdlEvent.key.key));

                m_Specification.EventCallback(
                    keyEvent);

                break;
            }
            case SDL_EVENT_WINDOW_RESIZED:
            {
                WindowResizeEvent event(
                    static_cast<uint32_t>(sdlEvent.window.data1),
                    static_cast<uint32_t>(sdlEvent.window.data2));

                m_Specification.EventCallback(event);

                break;
            }
            }
        }
    }

    void SDLWindow::SetEventCallback(
        const EventCallbackFn &callback)
    {
        m_Specification.EventCallback = callback;
    }
}