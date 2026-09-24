#include <Aurora/Scene/Components/ScriptableEntity.h>
#include <Aurora/Scene/Components/TransformComponent.h>
#include <Aurora/Math/Vector2.h>

#include <cmath>

using namespace Aurora;

namespace Aurora
{

    class OrbiterScript final : public ScriptableEntity
    {
    public:
        OrbiterScript(float radius, float angularSpeed, float phase)
            : m_Radius(radius), m_Speed(angularSpeed), m_Angle(phase) {}

    protected:
        void OnUpdate(float dt) override
        {
            m_Angle += m_Speed * dt;
            auto &tc = GetEntity().GetComponent<TransformComponent>();
            tc.LocalTransform.Position = Vector2{m_Radius, 0.0f}.Rotated(m_Angle);

            // Gentle pulse.
            const float pulse = 0.85f + 0.15f * std::sin(m_Angle * 3.0f);
            constexpr float RelativeSize = 56.0f / 72.0f;
            tc.LocalTransform.Scale = {RelativeSize * pulse, RelativeSize * pulse};
        }

    private:
        float m_Radius;
        float m_Speed;
        float m_Angle;
    };

}
