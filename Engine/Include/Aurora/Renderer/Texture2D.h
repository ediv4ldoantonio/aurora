#pragma once

#include <memory>
#include <string>

namespace Aurora
{

    class Texture2D
    {
    public:
        virtual ~Texture2D() = default;

        virtual uint32_t GetWidth() const = 0;

        virtual uint32_t GetHeight() const = 0;

        virtual void Bind(uint32_t slot = 0) const = 0;

        virtual void Unbind() const = 0;

        virtual bool IsLoaded() const = 0;

        virtual const std::string &GetPath() const = 0;

        static std::shared_ptr<Texture2D>
        Create(const std::string &path);
    };

}