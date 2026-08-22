#pragma once

#include "Aurora/Math/Vector2.h"
#include "Aurora/Renderer/Material.h"
#include "Aurora/Renderer/RenderSortKey.h"

namespace Aurora
{
    struct SpriteDrawCommand
    {
        Vector2 Position;

        Vector2 Size;

        float Rotation = 0.0f;

        Material *MaterialInstance = nullptr;

        RenderSortKey SortKey;
    };
}