#pragma once

#include "Aurora/Renderer/Framebuffer.h"

namespace Aurora
{
    class OpenGLFramebuffer : public Framebuffer
    {
    public:
        explicit OpenGLFramebuffer(
            const FramebufferSpecification &specification);

        ~OpenGLFramebuffer() override;

        void Bind() override;
        void Unbind() override;

        void Resize(
            uint32_t width,
            uint32_t height) override;

        uint32_t GetWidth() const override;
        uint32_t GetHeight() const override;

        std::shared_ptr<Texture2D>
        GetColorAttachment() const override;

    private:
        void Invalidate();

    private:
        FramebufferSpecification m_Specification;

        uint32_t m_RendererID = 0;
        uint32_t m_ColorAttachment = 0;
        uint32_t m_DepthStencilAttachment = 0;

        std::shared_ptr<Texture2D>
            m_ColorTexture;
    };
}