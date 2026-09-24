#pragma once

#include <Aurora/Scene/Components/ScriptableEntity.h>
#include <Aurora/Scene/Components/TransformComponent.h>
#include <Aurora/Scene/Components/SpriteComponent.h>
#include <Aurora/Math/Vector2.h>

using namespace Aurora;

namespace Sandbox
{
    class ProjectileScript final : public ScriptableEntity
    {
    public:
        ProjectileScript(Vector2 velocity, float lifetime) : m_Velocity(velocity), m_Lifetime(lifetime) {}

    protected:
        void OnUpdate(float dt) override
        {
            m_Age += dt;

            if (m_Age >= m_Lifetime)
            {
                GetEntity().Destroy();
                return;
            }

            auto &tc = GetEntity().GetComponent<TransformComponent>();

            tc.LocalTransform.Position += m_Velocity * dt;

            const float t = m_Age / m_Lifetime;

            auto &sprite = GetEntity().GetComponent<SpriteComponent>();

            auto &material = sprite.MaterialInstance;

            auto &color = material->GetTint();

            material->SetTint(Color{
                color.R,
                color.G,
                color.B,
                1.0f - t * t});

            const float s = 0.6f + 0.6f * t;

            tc.LocalTransform.Scale = {s, s};
        }

    private:
        Vector2 m_Velocity;
        float m_Lifetime;
        float m_Age = 0.0f;
    };
}
