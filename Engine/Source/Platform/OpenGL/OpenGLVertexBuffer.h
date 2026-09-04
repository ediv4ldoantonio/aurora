#pragma once

#include "Aurora/Renderer/VertexBuffer.h"

namespace Aurora
{
    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        explicit OpenGLVertexBuffer(size_t size);
        ~OpenGLVertexBuffer() override;

        void SetData(const void *data, size_t size) override;

        size_t GetCapacity() const override;

        void SetLayout(const BufferLayout &layout) override;
        const BufferLayout &GetLayout() const override;

        void Bind() const override;
        void Unbind() const override;

    private:
        uint32_t m_RendererID = 0;
        size_t m_Capacity = 0;
        BufferLayout m_Layout;
    };
}