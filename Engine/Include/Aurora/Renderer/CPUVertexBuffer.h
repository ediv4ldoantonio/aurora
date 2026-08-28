#pragma once
#include "Aurora/Renderer/VertexBuffer.h"
#include "Aurora/Renderer/BufferLayout.h"

#include <vector>

namespace Aurora
{
    class CPUVertexBuffer : public VertexBuffer
    {
    public:
        explicit CPUVertexBuffer(
            size_t size);

        void SetData(
            const void *data,
            size_t size) override;

        size_t GetCapacity() const override;

        void SetLayout(
            const BufferLayout &layout) override;

        const BufferLayout &
        GetLayout() const override;

    private:
        std::vector<std::byte> m_Data;
        BufferLayout m_Layout;
    };
}