#pragma once

#include "Aurora/Math/Vector2.h"
#include "Aurora/Renderer/Material.h"
#include "Aurora/Renderer/RenderSortKey.h"
#include "Aurora/Renderer/BatchKey.h"

namespace Aurora
{
    struct SpriteDrawCommand
    {
        Vector2 Position;

        Vector2 Size;

        float Rotation = 0.0f;

        Material *MaterialInstance = nullptr;

        RenderSortKey SortKey;

        BatchKey Batch;

        bool CanReorderForBatching() const
        {
            return MaterialInstance != nullptr &&
                   MaterialInstance->IsOpaque();
        }
    };
}