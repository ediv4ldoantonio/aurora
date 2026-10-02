#pragma once

#include "Aurora/Assets/Asset.h"

#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace Aurora
{
    class AudioClip : public Asset
    {
    public:
        virtual ~AudioClip() = default;

        static std::shared_ptr<AudioClip> Create(
            const std::string &path);

        AssetType GetType() const override
        {
            return AssetType::AudioClip;
        }

        const uint8_t *GetData() const
        {
            return m_Data.data();
        }

        size_t GetDataSize() const
        {
            return m_Data.size();
        }

        int GetSampleRate() const
        {
            return m_SampleRate;
        }

        int GetChannels() const
        {
            return m_Channels;
        }

        uint16_t GetFormat() const
        {
            return m_Format;
        }

    protected:
        explicit AudioClip(
            std::string path = {})
            : Asset(std::move(path))
        {
        }

        std::vector<uint8_t> m_Data;
        uint16_t m_Format = 0;
        int m_SampleRate = 0;
        int m_Channels = 0;
    };
}