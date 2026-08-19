#include <Aurora/Core/Application.h>
#include <Aurora/Core/Logger.h>
#include <Aurora/Core/Window.h>
#include <Aurora/Core/Time.h>
#include <Aurora/Input/Input.h>
#include <Aurora/Renderer/Renderer2D.h>
#include <Aurora/Events/ApplicationEvents.h>
#include <Aurora/Events/EventDispatcher.h>

namespace Aurora
{
    Application::Application()
        : m_Running(true)
    {
        Initialize();
    }

    Application::~Application()
    {
        Shutdown();
    }

    void Application::Run()
    {
        AURORA_LOG_INFO("Starting application loop");

        while (m_Running)
        {
            Time::Update();

            Input::Update();

            m_Window->OnUpdate();

            for (auto &layer : m_LayerStack)
            {
                layer->OnUpdate(
                    Time::DeltaTime());

                layer->OnRender();
            }
        }

        AURORA_LOG_INFO("Application loop exited");
    }

    void Application::Initialize()
    {
        Logger::Initialize();
        Logger::SetLevel(LogLevel::Trace);
        AURORA_LOG_INFO("Starting Aurora application");

        WindowSpecification spec;

        spec.Title =
            "Aurora Sandbox";

        spec.Width = 1280;

        spec.Height = 720;

        m_Window =
            Window::Create(spec);

        m_Window->SetEventCallback(
            [this](Event &event)
            {
                OnEvent(event);
            });

        AURORA_LOG_INFO("Created window: ", spec.Title, " (", spec.Width, "x", spec.Height, ")");

        Renderer2D::Init(
            m_Window
                ->GetGraphicsContext()
                .GetRendererAPI());
    }

    void Application::Shutdown()
    {
        AURORA_LOG_INFO("Shutting down Aurora application");
        Logger::Shutdown();
    }

    void Application::OnEvent(
        Event &event)
    {
        m_LayerStack.OnEvent(event);

        Input::ProcessEvent(event);

        EventDispatcher dispatcher(event);

        dispatcher.Dispatch<WindowCloseEvent>(
            [this](WindowCloseEvent &)
            {
                m_Running = false;

                AURORA_LOG_INFO("Closing application because the window requested shutdown");

                return true;
            });
    }

}