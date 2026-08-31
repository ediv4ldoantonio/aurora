#pragma once

#include "Aurora/Renderer/BufferLayout.h"

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

        virtual void SetLayout(
            const BufferLayout &layout) = 0;

        virtual const BufferLayout &
        GetLayout() const = 0;

        static std::shared_ptr<VertexBuffer> Create(
            size_t size);
    };
}