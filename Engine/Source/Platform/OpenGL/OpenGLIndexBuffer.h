#pragma once

#include "Aurora/Renderer/IndexBuffer.h"

namespace Aurora
{
    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(size_t count);

        ~OpenGLIndexBuffer() override;

        void SetData(
            const uint32_t *indices,
            size_t count) override;

        size_t GetCount() const override;

        void Bind() const override;
        void Unbind() const override;

    private:
        uint32_t m_RendererID = 0;
        size_t m_Count = 0;
    };
}