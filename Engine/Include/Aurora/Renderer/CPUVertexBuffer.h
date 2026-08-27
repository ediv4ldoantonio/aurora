#include "Aurora/Renderer/VertexBuffer.h"

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

    private:
        std::vector<std::byte> m_Data;
    };
}