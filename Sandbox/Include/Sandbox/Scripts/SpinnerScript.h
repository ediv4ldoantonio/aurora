#include <Aurora/Scene/Components/ScriptableEntity.h>
#include <Aurora/Scene/Components/TransformComponent.h>

using namespace Aurora;

namespace Sandbox
{
    class SpinnerScript final : public ScriptableEntity
    {
    public:
        explicit SpinnerScript(float speed) : m_Speed(speed) {}

    protected:
        void OnUpdate(float dt) override
        {
            GetEntity().GetComponent<TransformComponent>().LocalTransform.Rotation += m_Speed * dt;
        }

    private:
        float m_Speed;
    };

}
