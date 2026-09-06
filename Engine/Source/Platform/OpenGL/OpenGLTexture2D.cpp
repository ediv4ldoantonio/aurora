#include "OpenGLTexture2D.h"

#include <glad/gl.h>

#define STB_IMAGE_IMPLEMENTATION

#include <stb_image.h>

#include <stdexcept>

namespace Aurora
{
    OpenGLTexture2D::OpenGLTexture2D(
        const std::string &path)
    {
        int width = 0;
        int height = 0;
        int channels = 0;

        stbi_set_flip_vertically_on_load(1);

        unsigned char *data =
            stbi_load(
                path.c_str(),
                &width,
                &height,
                &channels,
                0);

        if (!data)
        {
            throw std::runtime_error(
                "Failed to load texture: " + path);
        }

        m_Width = static_cast<uint32_t>(width);
        m_Height = static_cast<uint32_t>(height);
        m_Channels = channels;

        GLenum internalFormat = 0;
        GLenum dataFormat = 0;

        if (m_Channels == 4)
        {
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
        }
        else if (m_Channels == 3)
        {
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
        }
        else
        {
            stbi_image_free(data);

            throw std::runtime_error(
                "Unsupported texture channel count: " +
                std::to_string(m_Channels));
        }

        glGenTextures(
            1,
            &m_RendererID);

        glBindTexture(
            GL_TEXTURE_2D,
            m_RendererID);

        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_MIN_FILTER,
            GL_LINEAR_MIPMAP_LINEAR);

        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_MAG_FILTER,
            GL_LINEAR);

        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_WRAP_S,
            GL_CLAMP_TO_EDGE);

        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_WRAP_T,
            GL_CLAMP_TO_EDGE);

        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            internalFormat,
            static_cast<GLsizei>(m_Width),
            static_cast<GLsizei>(m_Height),
            0,
            dataFormat,
            GL_UNSIGNED_BYTE,
            data);

        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(
            GL_TEXTURE_2D,
            0);

        stbi_image_free(data);
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        if (m_RendererID != 0)
        {
            glDeleteTextures(
                1,
                &m_RendererID);

            m_RendererID = 0;
        }
    }

    void OpenGLTexture2D::Bind(
        uint32_t slot) const
    {
        glActiveTexture(
            GL_TEXTURE0 + slot);

        glBindTexture(
            GL_TEXTURE_2D,
            m_RendererID);
    }

    void OpenGLTexture2D::Unbind() const
    {
        glBindTexture(
            GL_TEXTURE_2D,
            0);
    }

    uint32_t OpenGLTexture2D::GetWidth() const
    {
        return m_Width;
    }

    uint32_t OpenGLTexture2D::GetHeight() const
    {
        return m_Height;
    }

    bool OpenGLTexture2D::IsLoaded() const
    {
        return m_RendererID != 0;
    }

    const std::string &
    OpenGLTexture2D::GetPath() const
    {
        return m_Path;
    }
}