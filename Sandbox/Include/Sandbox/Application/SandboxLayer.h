#pragma once

#include <Aurora/Core/Layer.h>
#include <Aurora/Scene/Scene.h>
#include <Aurora/Renderer/Texture2D.h>
#include <Aurora/Renderer/Material.h>

#include <memory>

using namespace Aurora;

namespace Sandbox
{
    constexpr float Tau = 6.28318530718f;

    class SandboxLayer final : public Layer
    {
    public:
        explicit SandboxLayer();

        void OnAttach() override;

        void OnDetach() override;

        void OnUpdate(float dt) override;

        void OnRender() override;

        void OnEvent(Event &event) override;

    private:
        void BuildScene();

        std::unique_ptr<Scene> m_Scene;
        Entity m_Player;

        std::shared_ptr<Material> m_CrateMaterial = nullptr;
        std::shared_ptr<Material> m_OrbMaterial = nullptr;

        float m_TitleTimer = 0.0f;
    };
};