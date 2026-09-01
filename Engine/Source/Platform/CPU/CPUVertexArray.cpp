#include "Aurora/Renderer/VertexArray.h"

#include <stdexcept>

namespace Aurora
{
    class CPUVertexArray : public VertexArray
    {
    public:
        void Bind() const override
        {
        }

        void Unbind() const override
        {
        }

        void AddVertexBuffer(
            const std::shared_ptr<VertexBuffer> &vertexBuffer)
            override
        {
            if (!vertexBuffer)
            {
                return;
            }

            m_VertexBuffers.push_back(
                vertexBuffer);
        }

        void SetIndexBuffer(
            const std::shared_ptr<IndexBuffer> &indexBuffer)
            override
        {
            m_IndexBuffer =
                indexBuffer;
        }

        const std::vector<
            std::shared_ptr<VertexBuffer>> &
        GetVertexBuffers() const override
        {
            return m_VertexBuffers;
        }

        const std::shared_ptr<IndexBuffer> &
        GetIndexBuffer() const override
        {
            return m_IndexBuffer;
        }

        bool HasIndexBuffer() const override
        {
            return m_IndexBuffer != nullptr;
        }

    private:
        std::vector<
            std::shared_ptr<VertexBuffer>>
            m_VertexBuffers;

        std::shared_ptr<IndexBuffer>
            m_IndexBuffer;
    };
}