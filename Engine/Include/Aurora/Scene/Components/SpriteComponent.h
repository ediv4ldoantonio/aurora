#pragma once

#include "Aurora/Scene/Components/Component.h"
#include "Aurora/Math/Vector2.h"
#include "Aurora/Renderer/Color.h"
#include "Aurora/Renderer/Texture2D.h"
#include "Aurora/Renderer/RenderPass.h"

namespace Aurora
{

    struct SpriteComponent : public Component
    {
        Aurora::Color Tint;

        std::shared_ptr<Texture2D> Texture;

        int32_t Layer = 0;

        SpriteComponent() = default;

        RenderPass Pass =
            RenderPass::World;

        explicit SpriteComponent(const Aurora::Color &tint)
            : Tint(tint)
        {
        }
    };

}