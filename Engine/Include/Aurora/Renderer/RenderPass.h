#pragma once

#include <cstdint>

namespace Aurora
{
    enum class RenderPass : uint8_t
    {
        Background = 0,
        World = 1,
        Transparent = 2,
        UI = 3,
        Debug = 4
    };

    inline bool IsTransparentPass(
        RenderPass pass)
    {
        return pass == RenderPass::Transparent;
    }
}