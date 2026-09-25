#include "Aurora/Core/Application.h"
#include "Aurora/Core/Logger.h"
#include "Aurora/Core/Window.h"
#include "Aurora/Core/Time.h"
#include "Aurora/Input/Input.h"
#include "Aurora/Renderer/Renderer2D.h"
#include "Aurora/Renderer/RendererAPI.h"
#include "Aurora/Events/ApplicationEvents.h"
#include "Aurora/Events/EventDispatcher.h"

namespace Aurora
{
    Application *Application::s_Instance = nullptr;

    Application::Application(const ApplicationSpecification &specification)
        : m_Running(true), m_Specification(specification)
    {

        Initialize();
    }

    Application::~Application()
    {
        AURORA_LOG_INFO("Shutting down Aurora application");

        m_LayerStack.Clear();
        m_AssetManager.Clear();
        Renderer2D::Shutdown();
        m_Window.reset();

        s_Instance = nullptr;
    }

    void Application::Run()
    {
        Time::Init();

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
        AURORA_ASSERT(s_Instance == nullptr, "Only one Application may exist at a time");
        s_Instance = this;

        AURORA_LOG_INFO("Aurora Engine starting: ", m_Specification.Name);

        Logger::SetLevel(LogLevel::Trace);

        WindowSpecification spec;

        spec.Title = m_Specification.Name;

        spec.Width = m_Specification.Width;

        spec.Height = m_Specification.Height;

        spec.Resizable = m_Specification.Resizable;

        spec.VSync = m_Specification.VSync;

        spec.Resizable = m_Specification.Resizable;

        spec.Backend =
            RendererBackend::OpenGL;

        m_Window =
            Window::Create(spec);

        m_Window->SetEventCallback(
            [this](Event &event)
            {
                OnEvent(event);
            });

        Renderer2D::Init(
            *m_Window);

        Time::Init();
    }

    void Application::Shutdown()
    {
        m_Running = false;
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
                Shutdown();

                AURORA_LOG_INFO("Closing application because the window requested shutdown");

                return true;
            });

        dispatcher.Dispatch<WindowResizeEvent>(
            [this](WindowResizeEvent &event)
            {
                Renderer2D::OnResize(
                    event.GetWidth(),
                    event.GetHeight());

                return true;
            });
    }

    Application &Application::Get()
    {
        AURORA_ASSERT(s_Instance != nullptr, "Application has not been created");
        return *s_Instance;
    }

    bool Application::Exists()
    {
        return s_Instance != nullptr;
    }

    AssetManager &Application::GetAssetManager()
    {
        return m_AssetManager;
    }

    Window &Application::GetWindow()
    {
        return *m_Window;
    }
}
