#pragma once

#include <memory>
#include <string>
#include <functional>

#include "Aurora/Renderer/GraphicsContext.h"
#include "Aurora/Events/Event.h"
#include "Aurora/Renderer/RendererBackend.h"

namespace Aurora
{
    using EventCallbackFn =
        std::function<void(Event &)>;
    struct WindowSpecification
    {

        std::string Title;

        unsigned int Width;
        unsigned int Height;

        EventCallbackFn EventCallback;

        RendererBackend Backend =
            RendererBackend::SDL;
    };

    class GraphicsContext;

    class Window
    {

    public:
        virtual ~Window();

        virtual void OnUpdate() = 0;

        virtual GraphicsContext &GetGraphicsContext() = 0;

        static std::unique_ptr<Window> Create(const WindowSpecification &specification = WindowSpecification{});

        virtual void SetEventCallback(
            const EventCallbackFn &callback) = 0;

    private:
        WindowSpecification m_Data;
    };
}