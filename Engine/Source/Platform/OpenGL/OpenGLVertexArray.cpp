#include "OpenGLVertexArray.h"

#include "OpenGLIndexBuffer.h"
#include "Aurora/Renderer/BufferLayout.h"

#include <glad/gl.h>

#include <stdexcept>

namespace Aurora
{
    OpenGLVertexArray::OpenGLVertexArray()
    {
        glGenVertexArrays(1, &m_RendererID);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        if (m_RendererID != 0)
        {
            glDeleteVertexArrays(1, &m_RendererID);
            m_RendererID = 0;
        }
    }

    void OpenGLVertexArray::Bind() const
    {
        glBindVertexArray(m_RendererID);
    }

    void OpenGLVertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(
        const std::shared_ptr<VertexBuffer> &vertexBuffer)
    {
        if (!vertexBuffer)
        {
            throw std::invalid_argument(
                "VertexArray cannot add a null VertexBuffer");
        }

        const auto &layout =
            vertexBuffer->GetLayout();

        if (layout.GetElements().empty())
        {
            throw std::runtime_error(
                "VertexBuffer must have a layout before being added");
        }

        Bind();
        vertexBuffer->Bind();

        for (const auto &element : layout)
        {
            GLenum componentType = 0;
            GLint componentCount = 0;
            GLboolean normalized = element.Normalized
                                       ? GL_TRUE
                                       : GL_FALSE;

            switch (element.Type)
            {
            case ShaderDataType::Float:
                componentType = GL_FLOAT;
                componentCount = 1;
                break;

            case ShaderDataType::Float2:
                componentType = GL_FLOAT;
                componentCount = 2;
                break;

            case ShaderDataType::Float3:
                componentType = GL_FLOAT;
                componentCount = 3;
                break;

            case ShaderDataType::Float4:
                componentType = GL_FLOAT;
                componentCount = 4;
                break;

            case ShaderDataType::Int:
                componentType = GL_INT;
                componentCount = 1;
                break;

            case ShaderDataType::Int2:
                componentType = GL_INT;
                componentCount = 2;
                break;

            case ShaderDataType::Int3:
                componentType = GL_INT;
                componentCount = 3;
                break;

            case ShaderDataType::Int4:
                componentType = GL_INT;
                componentCount = 4;
                break;

            case ShaderDataType::UByte4:
                componentType = GL_UNSIGNED_BYTE;
                componentCount = 4;
                break;

            case ShaderDataType::Bool:
                componentType = GL_BOOL;
                componentCount = 1;
                break;

            default:
                throw std::runtime_error(
                    "Unsupported ShaderDataType");
            }

            glEnableVertexAttribArray(
                m_VertexAttributeIndex);

            glVertexAttribPointer(
                m_VertexAttributeIndex,
                componentCount,
                componentType,
                normalized,
                static_cast<GLsizei>(
                    layout.GetStride()),
                reinterpret_cast<const void *>(
                    element.Offset));

            ++m_VertexAttributeIndex;
        }

        m_VertexBuffers.push_back(vertexBuffer);

        Unbind();
    }

    void OpenGLVertexArray::SetIndexBuffer(
        const std::shared_ptr<IndexBuffer> &indexBuffer)
    {
        if (!indexBuffer)
        {
            throw std::invalid_argument(
                "VertexArray cannot use a null IndexBuffer");
        }

        Bind();
        indexBuffer->Bind();

        m_IndexBuffer = indexBuffer;

        Unbind();
    }

    const std::vector<
        std::shared_ptr<VertexBuffer>> &
    OpenGLVertexArray::GetVertexBuffers() const
    {
        return m_VertexBuffers;
    }

    const std::shared_ptr<IndexBuffer> &
    OpenGLVertexArray::GetIndexBuffer() const
    {
        return m_IndexBuffer;
    }

    bool OpenGLVertexArray::HasIndexBuffer() const
    {
        return m_IndexBuffer != nullptr;
    }
}