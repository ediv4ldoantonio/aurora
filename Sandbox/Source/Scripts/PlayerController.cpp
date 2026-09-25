#include <Aurora/Scene/Scene.h>
#include <Aurora/Scene/Components/ScriptableEntity.h>
#include <Aurora/Scene/Components/TransformComponent.h>
#include <Aurora/Scene/Components/SpriteComponent.h>
#include <Aurora/Scene/Components/ScriptComponent.h>
#include <Aurora/Input/Input.h>
#include <Aurora/Input/KeyCodes.h>
#include <Aurora/Assets/AssetManager.h>
#include <Aurora/Core/Application.h>
#include <Aurora/Renderer/Texture2D.h>

#include <string>

#include "Sandbox/Scripts/PlayerController.h"
#include "Sandbox/Scripts/ProjectileScript.h"

namespace Sandbox
{

    void PlayerController::OnCreate()
    {
        const std::string dir = AURORA_SANDBOX_ASSET_DIR;

        AssetManager &assets = Application::Get().GetAssetManager();

        m_OrbTexture = assets.LoadShared<Texture2D>(dir + "/Textures/orb.png");
    }

    void PlayerController::OnUpdate(float dt)
    {
        Vector2 dir{0.0f, 0.0f};

        if (Input::IsKeyDown(Key::A) || Input::IsKeyDown(Key::Left))
            dir.x -= 1.0f;
        if (Input::IsKeyDown(Key::D) || Input::IsKeyDown(Key::Right))
            dir.x += 1.0f;
        if (Input::IsKeyDown(Key::W) || Input::IsKeyDown(Key::Up))
            dir.y += 1.0f; // +Y is down
        if (Input::IsKeyDown(Key::S) || Input::IsKeyDown(Key::Down))
            dir.y -= 1.0f;

        auto &tc = GetEntity().GetComponent<TransformComponent>();

        if (dir.LengthSquared() > 0.0f)
        {
            dir = dir.Normalized();
            m_Velocity = dir * Speed;
            tc.LocalTransform.Position += m_Velocity * dt;
            tc.LocalTransform.Rotation = std::sin(static_cast<float>(Time::GetElapsedTime()) * 10.0f) * 0.08f;
        }
        else
        {
            m_Velocity = {0.0f, 0.0f};
            tc.LocalTransform.Rotation *= 0.9f;
        }

        if (Input::IsKeyPressed(Key::Space))
            FireBurst(tc.WorldTransform.Position);
    }

    void PlayerController::FireBurst(Vector2 origin)
    {
        Scene *scene = GetEntity().GetScene();

        constexpr int Count = 16;
        constexpr float Tau = 6.28318530718f;

        for (int i = 0; i < Count; ++i)
        {
            const float angle = (static_cast<float>(i) / Count) * Tau;

            const Vector2 dir = Vector2{1.0f, 0.0f}.Rotated(angle);

            Entity e = scene->CreateEntity("Projectile");

            auto &transform = e.GetComponent<TransformComponent>();

            transform.LocalTransform.Position = origin;

            transform.LocalTransform.Scale = {40.0f, 40.0f};

            auto material = std::make_shared<Material>(m_OrbTexture);

            material->SetTint(Color(255.0f, 0.8f * 255, 0.3f * 255, 255.0f));

            auto &sprite = e.AddComponent<SpriteComponent>(material);

            sprite.Layer = 5;

            e.AddComponent<ScriptComponent>().Bind<ProjectileScript>(dir * 380.0f, 1.2f);
        }
    }
}
