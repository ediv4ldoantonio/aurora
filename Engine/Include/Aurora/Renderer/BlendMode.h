#pragma once

#include <cstdint>

namespace Aurora
{
    enum class BlendMode : uint8_t
    {
        Opaque = 0,
        Alpha,
        Additive,
        Multiply
    };
}