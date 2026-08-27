#pragma once

#include <cstddef>
#include <memory>

namespace Aurora
{
    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() = default;

        virtual void SetData(
            const void *data,
            size_t size) = 0;

        virtual size_t GetCapacity() const = 0;

        static std::unique_ptr<VertexBuffer> Create(
            size_t size);
    };
}