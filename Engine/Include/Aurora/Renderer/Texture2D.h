#pragma once

#include "Aurora/Assets/Asset.h"

#include <memory>
#include <string>

namespace Aurora
{
    struct TextureSpecification
    {
        uint32_t Width = 0;
        uint32_t Height = 0;
    };

    class Texture2D : public Asset
    {
    public:
        virtual ~Texture2D() = default;

        virtual uint32_t GetWidth() const = 0;

        virtual uint32_t GetHeight() const = 0;

        virtual void Bind(uint32_t slot = 0) const = 0;

        virtual void Unbind() const = 0;

        virtual bool IsLoaded() const = 0;

        virtual const std::string &GetPath() const = 0;

        AssetType GetType() const override
        {
            return AssetType::Texture2D;
        }

        static std::shared_ptr<Texture2D>
        Create(const std::string &path);

        static std::shared_ptr<Texture2D>
        Create(
            const TextureSpecification &specification);
    };

}