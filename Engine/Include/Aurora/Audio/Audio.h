#pragma once

#include "Aurora/Audio/AudioClip.h"

namespace Aurora
{
    class Audio
    {
    public:
        static bool Init();
        static void Shutdown();
        static bool IsInitialized();

        static bool Play(
            AudioClip *clip);
    };
}