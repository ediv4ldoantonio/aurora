#pragma once

#include "Aurora/Core/LayerStack.h"
#include "Aurora/Assets/AssetManager.h"

#include <memory>
#include <string>

namespace Aurora
{
    class Window;

    struct ApplicationSpecification
    {
        std::string Name = "Aurora Application";
        uint32_t Width = 1280;
        uint32_t Height = 720;
        bool VSync = true;
        bool Resizable = true;
    };

    class Application
    {
    public:
        Application(const ApplicationSpecification &specification = ApplicationSpecification());
        ~Application();

        void Run();

        void PushLayer(
            std::unique_ptr<Layer> layer)
        {
            m_LayerStack.PushLayer(
                std::move(layer));
        }

        void PushOverlay(
            std::unique_ptr<Layer> layer)
        {
            m_LayerStack.PushOverlay(
                std::move(layer));
        }

        void OnEvent(
            Event &event);

        static Application &Get();
        static bool Exists();

        AssetManager &GetAssetManager();

        void Shutdown();

        Window &GetWindow();

    private:
        void Initialize();

    private:
        std::unique_ptr<Window> m_Window;
        ApplicationSpecification m_Specification;
        AssetManager m_AssetManager;
        LayerStack m_LayerStack;
        bool m_Running;

        static Application *s_Instance;
    };
}