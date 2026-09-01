#include "Aurora/Renderer/VertexBuffer.h"
#include "Aurora/Renderer/BufferLayout.h"

#include <vector>
#include <cstring>
#include <cstddef>

namespace Aurora
{
    class CPUVertexBuffer : public VertexBuffer
    {
    public:
        explicit CPUVertexBuffer(
            size_t size)
            : m_Data(size) {
              };

        void SetData(
            const void *data,
            size_t size) override
        {
            if (size > m_Data.size())
                return;

            std::memcpy(
                m_Data.data(),
                data,
                size);
        }

        size_t GetCapacity() const override
        {
            return m_Data.size();
        }

        void SetLayout(
            const BufferLayout &layout) override
        {
            m_Layout = layout;
        };

        const BufferLayout &
        GetLayout() const override
        {
            return m_Layout;
        }

    private:
        std::vector<std::byte> m_Data;
        BufferLayout m_Layout;
    };
}