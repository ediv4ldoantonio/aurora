#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>

namespace Aurora
{
    class IndexBuffer
    {
    public:
        virtual ~IndexBuffer() = default;

        virtual void SetData(
            const uint32_t *data,
            size_t count) = 0;

        virtual size_t GetCount() const = 0;

        static std::shared_ptr<IndexBuffer> Create(
            size_t count);
    };
}