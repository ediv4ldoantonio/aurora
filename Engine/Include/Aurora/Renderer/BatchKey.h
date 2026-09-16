#pragma once

#include "Aurora/Renderer/RenderPass.h"
#include "Aurora/Renderer/BlendMode.h"

#include <cstdint>

namespace Aurora
{
    struct BatchKey
    {
        RenderPass Pass =
            RenderPass::World;

        Aurora::BlendMode BlendMode =
            Aurora::BlendMode::Opaque;

        bool operator==(
            const BatchKey &other) const
        {
            return Pass == other.Pass &&
                   BlendMode == other.BlendMode;
        }

        bool operator<(
            const BatchKey &other) const
        {
            if (Pass != other.Pass)
            {
                return static_cast<uint8_t>(Pass) <
                       static_cast<uint8_t>(other.Pass);
            }

            return BlendMode <
                   other.BlendMode;
        }
    };
}