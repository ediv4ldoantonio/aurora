#include <Aurora/Core/Application.h>
#include <Aurora/Core/Logger.h>
#include <Aurora/Input/Input.h>
#include <Aurora/Input/KeyCodes.h>
#include <Aurora/Renderer/Renderer2D.h>
#include <Aurora/Core/Time.h>
#include <Aurora/Core/Window.h>
#include <Aurora/Scene/Components/IDComponent.h>
#include <Aurora/Scene/Components/ScriptComponent.h>

#include "Sandbox/Application/SandboxLayer.h"
#include "Sandbox/Scripts/PlayerController.h"
#include "Sandbox/Scripts/SpinnerScript.h"
#include "Sandbox/Scripts/OrbiterScript.h"

#include <string>
#include <cmath>

namespace Sandbox
{
    namespace
    {
        std::shared_ptr<Material> CreateMaterialInstance(
            const std::shared_ptr<Texture2D> &source)
        {
            if (!source)
                return nullptr;

            return std::make_shared<Material>(source);
        }
    }

    SandboxLayer::SandboxLayer() : Layer("Sandbox")
    {
    }

    void SandboxLayer::OnAttach()
    {
        const std::string dir = AURORA_SANDBOX_ASSET_DIR;

        AssetManager &assets = Application::Get().GetAssetManager();

        m_CrateTexture = assets.LoadShared<Texture2D>(dir + "/Textures/crate.png");

        m_OrbTexture = assets.LoadShared<Texture2D>(dir + "/Textures/orb.png");

        if (!m_CrateTexture || !m_OrbTexture)
            AURORA_LOG_WARN("Sandbox material missing in '{}': sprites will render as flat colors", dir);

        m_Scene = std::make_unique<Scene>();

        BuildScene();
    }

    void SandboxLayer::OnDetach()
    {
        m_Scene.reset();
    }

    void SandboxLayer::OnUpdate(float dt)
    {

        if (Input::IsKeyPressed(Key::Escape))
            Application::Get().Shutdown();
        if (Input::IsKeyPressed(Key::R))
            BuildScene();

        Camera2D &cam = m_Scene->GetCamera();

        if (Input::IsKeyDown(Key::E))
        {
            cam.SetZoom(cam.GetZoom() * (1.0f + 1.5f * dt));
        }
        if (Input::IsKeyDown(Key::Q))
        {
            cam.SetZoom(cam.GetZoom() / (1.0f + 1.5f * dt));
        }

        cam.SetZoom(std::clamp(cam.GetZoom(), 0.25f, 4.0f));

        // Smoothly follow the player. Exponential smoothing keeps it frame-rate independent.
        if (m_Player.IsValid())
        {
            const Vector2 target = m_Player.GetComponent<TransformComponent>().WorldTransform.Position;

            const float k = 1.0f - std::exp(-6.0f * dt);
            cam.SetPosition(cam.GetPosition() + (target - cam.GetPosition()) * k);
        }

        m_Scene->OnUpdate(dt);

        m_TitleTimer += dt;

        if (m_TitleTimer >= 0.5f)
        {
            m_TitleTimer = 0.0f;
            const auto &stats = Renderer2D::GetStatistics();
            char title[160];
            std::snprintf(title, sizeof(title),
                          "Aurora Sandbox | %.0f FPS | entities %zu | sprites %u | batches %u",
                          Time::GetFPS(), m_Scene->GetEntityCount(), stats.SpriteCount, stats.BatchCount);

            Application::Get().GetWindow().SetTitle(title);
        }
    }

    void SandboxLayer::OnRender()
    {
        m_Scene->OnRender();
    }

    void SandboxLayer::OnEvent(Event &event)
    {
    }

    void SandboxLayer::BuildScene()
    {
        std::vector<Entity> all;

        m_Scene->GetAllEntitiesWith<IDComponent>()
            .Each([&](EntityID id, IDComponent &component)
                  { all.push_back(m_Scene->GetEntityByUUID(component.ID)); });

        for (Entity e : all)
            if (e.IsValid() && !e.GetParent().IsValid())
                m_Scene->DestroyEntity(e);

        // Background: a checkerboard of dim crates on layer -10.
        constexpr int Half = 14;
        constexpr float Tile = 92.0f;
        for (int y = -Half; y <= Half; ++y)
        {
            for (int x = -Half; x <= Half; ++x)
            {
                Entity tile = m_Scene->CreateEntity("Tile");

                tile.GetComponent<TransformComponent>().LocalTransform.Position = {x * Tile, y * Tile};
                tile.GetComponent<TransformComponent>().LocalTransform.Scale = {Tile - 6.0f, Tile - 6.0f};

                const bool dark = ((x + y) & 1) != 0;

                const float v = dark ? 0.22f : 0.32f;

                auto material = CreateMaterialInstance(m_CrateTexture);

                material->SetTint(Color(v * 0.8f * 255.0f, v * 0.9f * 255.0f, v * 1.4f * 255.0f, 255.0f));

                auto &s = tile.AddComponent<SpriteComponent>(material);

                s.Layer = -10;
            }
        }

        // A few floating spinners at gameplay layer 0 (they occasionally overlap the player).
        for (int i = 0; i < 12; ++i)
        {
            const float a = (static_cast<float>(i) / 12.0f) * Tau;

            Entity e = m_Scene->CreateEntity("Spinner");

            e.GetComponent<TransformComponent>().LocalTransform.Position = Vector2{420.0f, 0.0f}.Rotated(a);
            e.GetComponent<TransformComponent>().LocalTransform.Scale = {64.0f, 64.0f};

            auto material = CreateMaterialInstance(m_CrateTexture);
            material->SetTint(Color(255.0f, 0.55f + 0.03f * i * 255.0f, 0.35f * 255.0f, 255.0f));

            auto &s = e.AddComponent<SpriteComponent>(material);

            s.Layer = 0;

            e.AddComponent<ScriptComponent>().Bind<SpinnerScript>((i & 1) ? 1.2f : -1.2f);
        }

        // The player, with a ring of orbiting orbs parented to it.
        m_Player = m_Scene->CreateEntity("Player");
        {
            auto material = CreateMaterialInstance(m_CrateTexture);
            material->SetTint(Color(0.6f * 255.0f, 0.9f * 255.0f, 255.0f, 255.0f));
            m_Player.GetComponent<TransformComponent>().LocalTransform.Scale = {72.0f, 72.0f};

            auto &s = m_Player.AddComponent<SpriteComponent>(material);

            s.Layer = 1;

            m_Player.AddComponent<ScriptComponent>().Bind<PlayerController>();
        }

        constexpr int Orbiters = 6;
        for (int i = 0; i < Orbiters; ++i)
        {
            Entity orb = m_Scene->CreateEntity("Orbiter");

            auto &transform = orb.GetComponent<TransformComponent>();

            transform.LocalTransform.Scale = Vector2{56.0f, 56.0f};

            auto material = CreateMaterialInstance(m_OrbTexture);
            material->SetTint(Color(0.4f + 0.1f * i * 255.0f, 0.9f - 0.1f * i * 255.0f, 255.0f, 255.0f));

            auto &s = orb.AddComponent<SpriteComponent>(material);

            s.Layer = 2;

            orb.AddComponent<ScriptComponent>().Bind<OrbiterScript>(
                110.0f + (i & 1) * 25.0f, (i & 1) ? -2.0f : 2.0f, (static_cast<float>(i) / Orbiters) * Tau);

            m_Scene->SetParent(orb, m_Player);
        }

        m_Scene->GetCamera().SetPosition({0.0f, 0.0f});
        m_Scene->GetCamera().SetZoom(1.0f);
    }
}