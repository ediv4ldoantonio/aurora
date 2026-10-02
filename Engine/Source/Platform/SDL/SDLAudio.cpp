#include "Aurora/Audio/Audio.h"
#include "Aurora/Core/Logger.h"

#include <SDL3/SDL.h>
#include <array>

namespace Aurora
{
    namespace
    {
        SDL_AudioDeviceID s_AudioDevice = 0;

        std::array<
            SDL_AudioStream *,
            Audio::MaxSimultaneousSounds>
            s_AudioStreams{};

        bool s_Initialized = false;

        SDL_AudioStream *FindAvailableStream()
        {
            for (auto *stream : s_AudioStreams)
            {
                if (!stream)
                    continue;

                if (SDL_GetAudioStreamAvailable(
                        stream) == 0)
                {
                    return stream;
                }
            }

            return nullptr;
        }
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

        for (auto &stream : s_AudioStreams)
        {
            stream = SDL_CreateAudioStream(
                nullptr,
                nullptr);

            if (!stream)
            {
                for (auto *createdStream : s_AudioStreams)
                {
                    if (createdStream)
                    {
                        SDL_DestroyAudioStream(
                            createdStream);
                    }
                }

                s_AudioStreams.fill(nullptr);

                SDL_CloseAudioDevice(
                    s_AudioDevice);

                s_AudioDevice = 0;

                SDL_QuitSubSystem(
                    SDL_INIT_AUDIO);

                return false;
            }
        }

        if (s_AudioDevice == 0)
        {
            SDL_QuitSubSystem(
                SDL_INIT_AUDIO);

            return false;
        }

        if (!SDL_BindAudioStreams(
                s_AudioDevice,
                s_AudioStreams.data(),
                static_cast<int>(
                    s_AudioStreams.size())))
        {
            for (auto *stream : s_AudioStreams)
            {
                if (stream)
                {
                    SDL_DestroyAudioStream(
                        stream);
                }
            }

            s_AudioStreams.fill(nullptr);

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

        for (auto *&stream : s_AudioStreams)
        {
            if (stream)
            {
                SDL_DestroyAudioStream(
                    stream);

                stream = nullptr;
            }
        }

        SDL_QuitSubSystem(
            SDL_INIT_AUDIO);

        s_Initialized = false;
    }

    bool Audio::IsInitialized()
    {
        return s_Initialized;
    }

    bool Audio::Play(
        AudioClip *clip)
    {
        if (!s_Initialized ||
            !clip)
        {
            return false;
        }

        SDL_AudioStream *stream =
            FindAvailableStream();

        if (!stream)
        {
            return false;
        }

        SDL_AudioSpec sourceSpec{};

        sourceSpec.format =
            static_cast<SDL_AudioFormat>(
                clip->GetFormat());

        sourceSpec.channels =
            clip->GetChannels();

        sourceSpec.freq =
            clip->GetSampleRate();

        if (!SDL_SetAudioStreamFormat(
                stream,
                &sourceSpec,
                nullptr))
        {
            return false;
        }

        SDL_ClearAudioStream(
            stream);

        if (!SDL_PutAudioStreamData(
                stream,
                clip->GetData(),
                static_cast<int>(
                    clip->GetDataSize())))
        {
            return false;
        }

        return SDL_FlushAudioStream(
            stream);
    }
}