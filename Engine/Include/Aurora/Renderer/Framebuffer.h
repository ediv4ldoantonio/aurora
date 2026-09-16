#pragma once

#include "Aurora/Renderer/Texture2D.h"

#include <cstdint>
#include <memory>

namespace Aurora
{
    struct FramebufferSpecification
    {
        uint32_t Width = 0;
        uint32_t Height = 0;

        bool HasDepthStencil = true;
    };

    class Framebuffer
    {
    public:
        virtual ~Framebuffer() = default;

        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        virtual void Resize(
            uint32_t width,
            uint32_t height) = 0;

        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;

        virtual std::shared_ptr<Texture2D>
        GetColorAttachment() const = 0;

        std::shared_ptr<Framebuffer>
        Create(
            const FramebufferSpecification &specification);
    };
}