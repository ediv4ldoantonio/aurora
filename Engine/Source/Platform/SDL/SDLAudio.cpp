#include "Aurora/Audio/Audio.h"
#include "Aurora/Core/Logger.h"

#include <SDL3/SDL.h>

namespace Aurora
{
    namespace
    {
        SDL_AudioDeviceID s_AudioDevice = 0;
        bool s_Initialized = false;
    }

    bool Audio::Init()
    {
        if (s_Initialized)
            return true;

        AURORA_LOG_INFO("Initializing SDL audio subsystem");

        if (!SDL_InitSubSystem(SDL_INIT_AUDIO))
            return false;

        s_AudioDevice =
            SDL_OpenAudioDevice(
                SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK,
                nullptr);

        if (s_AudioDevice == 0)
        {
            SDL_QuitSubSystem(
                SDL_INIT_AUDIO);

            return false;
        }

        s_Initialized = true;

        return true;
    }

    void Audio::Shutdown()
    {
        if (!s_Initialized)
            return;

        if (s_AudioDevice != 0)
        {
            SDL_CloseAudioDevice(
                s_AudioDevice);

            s_AudioDevice = 0;
        }

        SDL_QuitSubSystem(
            SDL_INIT_AUDIO);

        s_Initialized = false;
    }

    bool Audio::IsInitialized()
    {
        return s_Initialized;
    }
}