#pragma once

#include "Aurora/Audio/AudioClip.h"

#include <string>

namespace Aurora
{
    class Audio
    {
    public:
        static bool Init();
        static void Shutdown();
        static bool IsInitialized();

        static bool PlayWAV(
            const std::string &path);

        static bool Play(
            AudioClip *clip);
    };
}