#pragma once

#include <cstdint>

namespace Aurora
{
    enum class MouseButton : uint8_t
    {
        Left = 0,
        Middle,
        Right,
        X1,
        X2
    };

    constexpr size_t MouseButtonCount = 5;
}