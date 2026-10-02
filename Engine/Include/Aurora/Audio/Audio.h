#pragma once

namespace Aurora
{
    class Audio
    {
    public:
        static bool Init();
        static void Shutdown();
        static bool IsInitialized();
    };
}