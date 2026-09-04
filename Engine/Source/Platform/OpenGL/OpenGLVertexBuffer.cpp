#include "OpenGLVertexBuffer.h"

#include <glad/gl.h>

#include <stdexcept>

namespace Aurora
{
    OpenGLVertexBuffer::OpenGLVertexBuffer(size_t size)
        : m_Capacity(size)
    {
        if (size == 0)
        {
            throw std::invalid_argument(
                "OpenGLVertexBuffer size cannot be zero");
        }

        glGenBuffers(1, &m_RendererID);

        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);

        glBufferData(
            GL_ARRAY_BUFFER,
            static_cast<GLsizeiptr>(size),
            nullptr,
            GL_DYNAMIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        if (m_RendererID != 0)
        {
            glDeleteBuffers(1, &m_RendererID);
            m_RendererID = 0;
        }
    }

    void OpenGLVertexBuffer::SetData(
        const void *data,
        size_t size)
    {
        if (size > m_Capacity)
        {
            throw std::runtime_error(
                "VertexBuffer data exceeds buffer capacity");
        }

        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);

        glBufferSubData(
            GL_ARRAY_BUFFER,
            0,
            static_cast<GLsizeiptr>(size),
            data);
    }

    size_t OpenGLVertexBuffer::GetCapacity() const
    {
        return m_Capacity;
    }

    void OpenGLVertexBuffer::SetLayout(
        const BufferLayout &layout)
    {
        m_Layout = layout;
    }

    const BufferLayout &
    OpenGLVertexBuffer::GetLayout() const
    {
        return m_Layout;
    }

    void OpenGLVertexBuffer::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    }

    void OpenGLVertexBuffer::Unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}