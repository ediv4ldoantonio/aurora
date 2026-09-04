#include "SDLWindow.h"
#include "Aurora/Events/ApplicationEvents.h"

#include "Aurora/Input/Input.h"
#include "Aurora/Core/Logger.h"
#include "Aurora/Events/KeyEvents.h"
#include "SDLKeyCodes.h"
#include "Aurora/Renderer/GraphicsContext.h"

#include <SDL3/SDL.h>

namespace Aurora
{
    SDLWindow::SDLWindow(const WindowSpecification &specification)
        : m_Specification(specification)
    {
        AURORA_LOG_INFO("Initializing SDL video subsystem");
        SDL_Init(SDL_INIT_VIDEO);

        SDL_WindowFlags flags =
            SDL_WINDOW_RESIZABLE;

        if (m_Specification.Backend ==
            RendererBackend::OpenGL)
        {
            flags =
                static_cast<SDL_WindowFlags>(
                    flags |
                    SDL_WINDOW_OPENGL);

            ConfigureOpenGLAttributes();
        }

        m_Window = SDL_CreateWindow(
            m_Specification.Title.c_str(),
            m_Specification.Width,
            m_Specification.Height,
            flags);

        if (!m_Window)
        {
            AURORA_LOG_ERROR("Failed to create window: ", m_Specification.Title);
        }

        m_Context = GraphicsContext::Create(m_Window, m_Specification.Backend);

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

    void SDLWindow::ConfigureOpenGLAttributes()
    {
        if (!SDL_GL_SetAttribute(
                SDL_GL_CONTEXT_MAJOR_VERSION,
                3))
        {
            throw std::runtime_error(
                "Failed to set OpenGL major version");
        }

        if (!SDL_GL_SetAttribute(
                SDL_GL_CONTEXT_MINOR_VERSION,
                3))
        {
            throw std::runtime_error(
                "Failed to set OpenGL minor version");
        }

        if (!SDL_GL_SetAttribute(
                SDL_GL_CONTEXT_PROFILE_MASK,
                SDL_GL_CONTEXT_PROFILE_CORE))
        {
            throw std::runtime_error(
                "Failed to set OpenGL core profile");
        }

        SDL_GL_SetAttribute(
            SDL_GL_DOUBLEBUFFER,
            1);

        SDL_GL_SetAttribute(
            SDL_GL_DEPTH_SIZE,
            24);
    }
}