#pragma once

#include "Aurora/Core/Window.h"

#include <memory>

struct SDL_Window;

namespace Aurora
{
    class SDLGraphicsContext;

    class SDLWindow : public Window
    {
    public:
        explicit SDLWindow(const WindowSpecification &specification);

        ~SDLWindow() override;

        void OnUpdate() override;

        void SetEventCallback(
            const EventCallbackFn &callback) override;

        GraphicsContext &GetGraphicsContext() override;

        unsigned int GetWidth() const override;

        unsigned int GetHeight() const override;

        void SetTitle(const std::string &title) override;

    private:
        static void ConfigureOpenGLAttributes();

        WindowSpecification m_Specification;
        SDL_Window *m_Window = nullptr;
        bool m_ShouldClose = false;
        std::unique_ptr<GraphicsContext> m_Context;
    };
}