#include "Aurora/Audio/AudioClip.h"

#include <SDL3/SDL.h>

namespace Aurora
{
    std::shared_ptr<AudioClip>
    AudioClip::Create(
        const std::string &path)
    {
        SDL_AudioSpec spec{};
        Uint8 *data = nullptr;
        Uint32 dataLength = 0;

        if (!SDL_LoadWAV(
                path.c_str(),
                &spec,
                &data,
                &dataLength))
        {
            return nullptr;
        }

        auto clip =
            std::shared_ptr<AudioClip>(
                new AudioClip(path));

        clip->m_Data.assign(
            data,
            data + dataLength);

        clip->m_SampleRate =
            spec.freq;

        clip->m_Channels =
            spec.channels;

        clip->m_Format =
            spec.format;

        SDL_free(data);

        return clip;
    }
}