#pragma once

#include <Aurora/Math/Vector2.h>
#include <Aurora/Core/Time.h>
#include <Aurora/Renderer/Material.h>

#include <cmath>
#include <memory>

using namespace Aurora;

namespace Sandbox
{
    class PlayerController final : public ScriptableEntity
    {
    protected:
        void OnUpdate(float dt) override;

        void OnCreate() override;

    private:
        void FireBurst(Vector2 origin);

        static constexpr float Speed = 320.0f;

        Vector2 m_Velocity{0.0f, 0.0f};

        std::shared_ptr<Material> m_OrbMaterial = nullptr;
    };
}