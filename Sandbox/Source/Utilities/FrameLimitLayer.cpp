#include <Aurora/Core/Layer.h>
#include <Aurora/Core/Application.h>

using namespace Aurora;

namespace Sandbox
{
    class FrameLimitLayer final : public Layer
    {
    public:
        explicit FrameLimitLayer(int frames) : Layer("FrameLimit"), m_Remaining(frames) {}

        void OnUpdate(float) override
        {
            if (--m_Remaining <= 0)
                Application::Get().Shutdown();
        }

    private:
        int m_Remaining;
    };
}
