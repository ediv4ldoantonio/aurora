#pragma once

#include "Aurora/Core/UUID.h"
#include "Aurora/Renderer/RenderPass.h"

#include <cstdint>

namespace Aurora
{
    struct BatchKey
    {
        RenderPass Pass =
            RenderPass::World;

        UUID MaterialID;

        bool operator==(
            const BatchKey &other) const
        {
            return Pass == other.Pass &&
                   MaterialID == other.MaterialID;
        }

        bool operator<(
            const BatchKey &other) const
        {
            if (Pass != other.Pass)
            {
                return static_cast<uint8_t>(Pass) <
                       static_cast<uint8_t>(other.Pass);
            }

            return MaterialID <
                   other.MaterialID;
        }
    };
}