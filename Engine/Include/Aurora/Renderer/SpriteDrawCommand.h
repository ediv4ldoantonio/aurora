#pragma once

#include "Aurora/Math/Vector2.h"
#include "Aurora/Renderer/Color.h"

namespace Aurora
{

    class Texture2D;

    struct SpriteDrawCommand
    {
        Vector2 Position;

        Vector2 Size;

        float Rotation;

        Color Tint;

        Texture2D *Texture;

        int32_t Layer = 0;
    };
}