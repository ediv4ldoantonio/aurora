#include "Aurora/Audio/Audio.h"
#include "Aurora/Core/Logger.h"

#include <SDL3/SDL.h>

namespace Aurora
{
    namespace
    {
        SDL_AudioDeviceID s_AudioDevice = 0;
        SDL_AudioStream *s_AudioStream = nullptr;
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

        s_AudioStream =
            SDL_CreateAudioStream(
                nullptr,
                nullptr);

        if (s_AudioDevice == 0)
        {
            SDL_QuitSubSystem(
                SDL_INIT_AUDIO);

            return false;
        }

        if (!s_AudioStream)
        {
            SDL_CloseAudioDevice(
                s_AudioDevice);

            s_AudioDevice = 0;

            SDL_QuitSubSystem(
                SDL_INIT_AUDIO);

            return false;
        }

        if (!SDL_BindAudioStream(
                s_AudioDevice,
                s_AudioStream))
        {
            SDL_DestroyAudioStream(
                s_AudioStream);

            s_AudioStream = nullptr;

            SDL_CloseAudioDevice(
                s_AudioDevice);

            s_AudioDevice = 0;

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

        if (s_AudioStream)
        {
            SDL_DestroyAudioStream(
                s_AudioStream);

            s_AudioStream = nullptr;
        }

        SDL_QuitSubSystem(
            SDL_INIT_AUDIO);

        s_Initialized = false;
    }

    bool Audio::IsInitialized()
    {
        return s_Initialized;
    }

    bool Audio::PlayWAV(
        const std::string &path)
    {
        if (!s_Initialized ||
            !s_AudioStream)
        {
            return false;
        }

        SDL_AudioSpec wavSpec{};
        Uint8 *wavBuffer = nullptr;
        Uint32 wavLength = 0;

        if (!SDL_LoadWAV(
                path.c_str(),
                &wavSpec,
                &wavBuffer,
                &wavLength))
        {
            return false;
        }

        SDL_ClearAudioStream(
            s_AudioStream);

        const bool putSuccess =
            SDL_PutAudioStreamData(
                s_AudioStream,
                wavBuffer,
                static_cast<int>(wavLength));

        SDL_free(wavBuffer);

        if (!putSuccess)
            return false;

        return SDL_FlushAudioStream(
            s_AudioStream);
    }
}