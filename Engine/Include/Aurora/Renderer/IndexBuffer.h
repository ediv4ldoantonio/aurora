#pragma once

#include <cstddef>
#include <cstdint>

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

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
    };
}