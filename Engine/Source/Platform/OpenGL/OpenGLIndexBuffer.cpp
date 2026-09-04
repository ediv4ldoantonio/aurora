#include "OpenGLIndexBuffer.h"

#include <glad/gl.h>

#include <stdexcept>

namespace Aurora
{
    OpenGLIndexBuffer::OpenGLIndexBuffer(size_t count)
        : m_Count(count)
    {
        if (count == 0)
        {
            throw std::invalid_argument(
                "OpenGLIndexBuffer count cannot be zero");
        }

        glGenBuffers(1, &m_RendererID);

        glBindBuffer(
            GL_ELEMENT_ARRAY_BUFFER,
            m_RendererID);

        glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            static_cast<GLsizeiptr>(
                count * sizeof(uint32_t)),
            nullptr,
            GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
        if (m_RendererID != 0)
        {
            glDeleteBuffers(1, &m_RendererID);
            m_RendererID = 0;
        }
    }

    void OpenGLIndexBuffer::SetData(
        const uint32_t *indices,
        size_t count)
    {
        if (!indices)
        {
            throw std::invalid_argument(
                "OpenGLIndexBuffer indices cannot be null");
        }

        if (count > m_Count)
        {
            throw std::runtime_error(
                "IndexBuffer data exceeds buffer capacity");
        }

        glBindBuffer(
            GL_ELEMENT_ARRAY_BUFFER,
            m_RendererID);

        glBufferSubData(
            GL_ELEMENT_ARRAY_BUFFER,
            0,
            static_cast<GLsizeiptr>(
                count * sizeof(uint32_t)),
            indices);
    }

    size_t OpenGLIndexBuffer::GetCount() const
    {
        return m_Count;
    }

    void OpenGLIndexBuffer::Bind() const
    {
        glBindBuffer(
            GL_ELEMENT_ARRAY_BUFFER,
            m_RendererID);
    }

    void OpenGLIndexBuffer::Unbind() const
    {
        glBindBuffer(
            GL_ELEMENT_ARRAY_BUFFER,
            0);
    }
}