#include "Aurora/Renderer/IndexBuffer.h"

#include <algorithm>
#include <vector>

namespace Aurora
{
    class CPUIndexBuffer : public IndexBuffer
    {
    public:
        explicit CPUIndexBuffer(
            size_t count)
            : m_Data(count),
              m_Count(count)
        {
        }

        void SetData(
            const uint32_t *data,
            size_t count) override
        {
            if (!data)
            {
                return;
            }

            if (count > m_Data.size())
            {
                return;
            }

            std::copy_n(
                data,
                count,
                m_Data.begin());

            m_Count = count;
        }

        size_t GetCount() const override
        {
            return m_Count;
        }

    private:
        std::vector<uint32_t> m_Data;

        size_t m_Count = 0;
    };
}