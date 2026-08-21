#pragma once

#include "Aurora/Renderer/RenderPass.h"

#include <cstdint>

namespace Aurora
{
    struct RenderSortKey
    {
        RenderPass Pass =
            RenderPass::World;

        int32_t Layer = 0;

        uint64_t SubmissionOrder = 0;

        bool operator<(
            const RenderSortKey &other) const
        {
            if (Pass != other.Pass)
            {
                return static_cast<uint8_t>(Pass) <
                       static_cast<uint8_t>(other.Pass);
            }

            if (Layer != other.Layer)
            {
                return Layer < other.Layer;
            }

            return SubmissionOrder <
                   other.SubmissionOrder;
        }
    };
}