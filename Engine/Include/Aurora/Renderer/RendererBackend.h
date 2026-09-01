#pragma once

#include <cstdint>

namespace Aurora
{
    enum class RendererBackend : uint8_t
    {
        None = 0,
        SDL,
        OpenGL
    };
}