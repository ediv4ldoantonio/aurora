#include "SandboxLayer.h"
#include <Aurora/Core/Logger.h>
#include <Aurora/Input/Input.h>
#include <Aurora/Renderer/Renderer2D.h>
#include <Aurora/Scene/Entity.h>
#include <Aurora/Scene/Components/IDComponent.h>
#include "Aurora/Events/Event.h"

#include <iostream>

SandboxLayer::SandboxLayer()
    : Layer("Sandbox")
{
    m_Scene =
        std::make_shared<Aurora::Scene>();

    m_Scene->GetCamera().SetPosition({0.0f, 0.0f});

    auto player =
        m_Scene->CreateEntity("Player");

    auto weapon =
        m_Scene->CreateEntity("Weapon");

    m_Scene->SetParent(weapon, player);

    auto &p_Transform =
        player.GetComponent<
            Aurora::TransformComponent>();

    p_Transform.LocalTransform.Position =
        {0, 0};

    p_Transform.LocalTransform.Scale =
        {100, 200};

    auto &w_Transform =
        weapon.GetComponent<
            Aurora::TransformComponent>();

    w_Transform.LocalTransform.Position =
        {100, 100};

    w_Transform.LocalTransform.Scale =
        {50, 50};

    player.AddComponent<Aurora::ScriptComponent>()
        .Bind<PlayerMovement>();

    player.AddComponent<
        Aurora::SpriteComponent>(Aurora::Color::Red);

    weapon.AddComponent<
        Aurora::SpriteComponent>(Aurora::Color::Blue);
}

void SandboxLayer::OnUpdate(float dt)
{
    m_Scene->OnUpdate(dt);
}

void SandboxLayer::OnRender()
{
    m_Scene->OnRender();
}

void SandboxLayer::OnEvent(
    Aurora::Event &event)
{
}