#include "OpenGLGraphicsContext.h"
#include "OpenGLRendererAPI.h"

#include "Aurora/Core/Logger.h"
#include "Aurora/Renderer/RendererAPI.h"

#include <SDL3/SDL.h>
#include <glad/gl.h>

#include <stdexcept>

namespace Aurora
{
    OpenGLGraphicsContext::
        OpenGLGraphicsContext(
            SDL_Window *window)
        : m_Window(window)
    {
        if (!m_Window)
        {
            throw std::invalid_argument(
                "OpenGLGraphicsContext received "
                "a null SDL_Window");
        }
    }

    void OpenGLGraphicsContext::Init()
    {
        if (!m_Window)
        {
            throw std::runtime_error(
                "Cannot initialize OpenGL without "
                "an SDL window");
        }

        m_Context =
            SDL_GL_CreateContext(
                m_Window);

        if (!m_Context)
        {
            throw std::runtime_error(
                std::string(
                    "Failed to create OpenGL context: ") +
                SDL_GetError());
        }

        if (!gladLoadGL(
                reinterpret_cast<GLADloadfunc>(
                    SDL_GL_GetProcAddress)))
        {
            throw std::runtime_error(
                "Failed to initialize GLAD");
        }

        const auto *version =
            reinterpret_cast<const char *>(
                glGetString(GL_VERSION));

        const auto *vendor =
            reinterpret_cast<const char *>(
                glGetString(GL_VENDOR));

        const auto *renderer =
            reinterpret_cast<const char *>(
                glGetString(GL_RENDERER));

        AURORA_LOG_TRACE(
            "OpenGL Version: ",
            version ? version : "unknown");

        AURORA_LOG_TRACE(
            "OpenGL Vendor: ",
            vendor ? vendor : "unknown");

        AURORA_LOG_TRACE(
            "OpenGL Renderer: ",
            renderer ? renderer : "unknown");

        if (!SDL_GL_SetSwapInterval(1))
        {
            AURORA_LOG_WARN(
                "Failed to enable VSync: ",
                SDL_GetError());
        }

        m_RendererAPI =
            std::make_unique<
                OpenGLRendererAPI>();
    }

    RendererAPI *
    OpenGLGraphicsContext::GetRendererAPI()
    {
        return m_RendererAPI.get();
    }

    void OpenGLGraphicsContext::SwapBuffers()
    {
        if (!m_Window)
            return;

        if (!SDL_GL_SwapWindow(m_Window))
        {
            AURORA_LOG_ERROR(
                "Failed to swap OpenGL buffers: ",
                SDL_GetError());
        }
    }

    OpenGLGraphicsContext::
        ~OpenGLGraphicsContext()
    {
        m_RendererAPI.reset();

        if (m_Context)
        {
            SDL_GL_DestroyContext(
                m_Context);

            m_Context = nullptr;
        }
    }

}