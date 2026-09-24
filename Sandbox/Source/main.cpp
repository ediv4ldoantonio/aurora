#include <Aurora/Core/Application.h>
#include <memory>

#include "Sandbox/Application/SandboxLayer.h"
#include "Sandbox/Utilities/FrameLimitLayer.h"

#include <cstring>

using namespace Aurora;

int main(int argc, char const *argv[])
{
    int maxFrames = 0;

    for (int i = 1; i < argc; ++i)
    {
        if (std::strcmp(argv[i], "--frames") == 0 && i + 1 < argc)
            maxFrames = std::atoi(argv[++i]);
    }

    ApplicationSpecification spec;

    spec.Name = "Aurora Sandbox";
    spec.Width = 1280;
    spec.Height = 720;
    spec.Resizable = true;

    Application app(spec);

    app.PushLayer(std::make_unique<Sandbox::SandboxLayer>());
    // if (maxFrames > 0)
    //     app.PushOverlay(std::make_unique<FrameLimitLayer>(maxFrames));

    app.Run();

    return 0;
}
