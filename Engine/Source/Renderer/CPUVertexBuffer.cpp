#include "Aurora/Renderer/CPUVertexBuffer.h"

#include <vector>
#include <cstring>
#include <cstddef>

namespace Aurora
{
    CPUVertexBuffer::CPUVertexBuffer(
        size_t size)
        : m_Data(size)
    {
    }

    void CPUVertexBuffer::SetData(
        const void *data,
        size_t size)
    {
        if (size > m_Data.size())
            return;

        std::memcpy(
            m_Data.data(),
            data,
            size);
    }

    void CPUVertexBuffer::SetLayout(
        const BufferLayout &layout)
    {
        m_Layout = layout;
    }

    const BufferLayout &
    CPUVertexBuffer::GetLayout() const
    {
        return m_Layout;
    }

    size_t CPUVertexBuffer::GetCapacity() const
    {
        return m_Data.size();
    }
}