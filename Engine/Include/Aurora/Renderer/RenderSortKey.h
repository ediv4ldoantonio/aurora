#pragma once

#include <cstdint>

namespace Aurora
{
    struct RenderSortKey
    {
        int32_t RenderPass = 0;

        int32_t Layer = 0;

        uint64_t SubmissionOrder = 0;

        bool operator<(
            const RenderSortKey &other) const
        {
            if (RenderPass !=
                other.RenderPass)
            {
                return RenderPass <
                       other.RenderPass;
            }

            if (Layer !=
                other.Layer)
            {
                return Layer <
                       other.Layer;
            }

            return SubmissionOrder <
                   other.SubmissionOrder;
        }
    };
}