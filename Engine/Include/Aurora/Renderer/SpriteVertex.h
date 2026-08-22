#pragma once

#include "Aurora/Math/Vector2.h"
#include "Aurora/Renderer/Color.h"

namespace Aurora
{

    struct SpriteVertex
    {
        Vector2 Position;
        Vector2 TexCoord;
        Aurora::Color Color;
        float MaterialIndex = 0.0f;
    };

}