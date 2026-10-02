#pragma once

#include "Aurora/Audio/AudioClip.h"

#include <cstddef>

namespace Aurora
{
    class Audio
    {
    public:
        static constexpr size_t MaxSimultaneousSounds = 16;
        static bool Init();
        static void Shutdown();
        static bool IsInitialized();

        static bool Play(
            AudioClip *clip);
    };
}