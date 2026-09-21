#include "OpenGLFramebuffer.h"
#include "OpenGLTexture2D.h"

#include <glad/gl.h>

#include <stdexcept>

namespace Aurora
{
    OpenGLFramebuffer::OpenGLFramebuffer(
        const FramebufferSpecification &specification)
        : m_Specification(specification)
    {
        if (specification.Width == 0 ||
            specification.Height == 0)
        {
            throw std::invalid_argument(
                "Framebuffer dimensions must be greater than zero");
        }

        Invalidate();
    }

    OpenGLFramebuffer::~OpenGLFramebuffer()
    {
        if (m_DepthStencilAttachment != 0)
        {
            glDeleteRenderbuffers(
                1,
                &m_DepthStencilAttachment);
        }

        if (m_RendererID != 0)
        {
            glDeleteFramebuffers(
                1,
                &m_RendererID);
        }
    }

    void OpenGLFramebuffer::Bind()
    {
        glBindFramebuffer(
            GL_FRAMEBUFFER,
            m_RendererID);

        glViewport(
            0,
            0,
            static_cast<GLsizei>(
                m_Specification.Width),
            static_cast<GLsizei>(
                m_Specification.Height));
    }

    void OpenGLFramebuffer::Unbind()
    {
        glBindFramebuffer(
            GL_FRAMEBUFFER,
            0);
    }

    void OpenGLFramebuffer::Resize(
        uint32_t width,
        uint32_t height)
    {
        if (width == 0 || height == 0)
            return;

        if (width == m_Specification.Width &&
            height == m_Specification.Height)
        {
            return;
        }

        m_Specification.Width = width;
        m_Specification.Height = height;

        Invalidate();
    }

    uint32_t OpenGLFramebuffer::GetWidth() const
    {
        return m_Specification.Width;
    }

    uint32_t OpenGLFramebuffer::GetHeight() const
    {
        return m_Specification.Height;
    }

    std::shared_ptr<Texture2D>
    OpenGLFramebuffer::GetColorAttachment() const
    {
        return m_ColorTexture;
    }

    void OpenGLFramebuffer::Invalidate()
    {
        if (m_DepthStencilAttachment != 0)
        {
            glDeleteRenderbuffers(
                1,
                &m_DepthStencilAttachment);

            m_DepthStencilAttachment = 0;
        }

        m_ColorTexture.reset();
        m_ColorAttachment = 0;

        if (m_RendererID != 0)
        {
            glDeleteFramebuffers(
                1,
                &m_RendererID);

            m_RendererID = 0;
        }

        glGenFramebuffers(
            1,
            &m_RendererID);

        glBindFramebuffer(
            GL_FRAMEBUFFER,
            m_RendererID);

        TextureSpecification textureSpecification;

        textureSpecification.Width =
            m_Specification.Width;

        textureSpecification.Height =
            m_Specification.Height;

        m_ColorTexture =
            Texture2D::Create(
                textureSpecification);

        auto *openGLTexture =
            dynamic_cast<OpenGLTexture2D *>(
                m_ColorTexture.get());

        if (!openGLTexture)
        {
            throw std::runtime_error(
                "Framebuffer requires OpenGLTexture2D");
        }

        m_ColorAttachment =
            openGLTexture->GetRendererID();

        glFramebufferTexture2D(
            GL_FRAMEBUFFER,
            GL_COLOR_ATTACHMENT0,
            GL_TEXTURE_2D,
            m_ColorAttachment,
            0);

        // Depth/stencil attachment
        if (m_Specification.HasDepthStencil)
        {
            glGenRenderbuffers(
                1,
                &m_DepthStencilAttachment);

            glBindRenderbuffer(
                GL_RENDERBUFFER,
                m_DepthStencilAttachment);

            glRenderbufferStorage(
                GL_RENDERBUFFER,
                GL_DEPTH24_STENCIL8,
                static_cast<GLsizei>(
                    m_Specification.Width),
                static_cast<GLsizei>(
                    m_Specification.Height));

            glFramebufferRenderbuffer(
                GL_FRAMEBUFFER,
                GL_DEPTH_STENCIL_ATTACHMENT,
                GL_RENDERBUFFER,
                m_DepthStencilAttachment);
        }

        if (glCheckFramebufferStatus(
                GL_FRAMEBUFFER) !=
            GL_FRAMEBUFFER_COMPLETE)
        {
            glBindFramebuffer(
                GL_FRAMEBUFFER,
                0);

            throw std::runtime_error(
                "OpenGL framebuffer is incomplete");
        }

        glBindFramebuffer(
            GL_FRAMEBUFFER,
            0);
    }
}