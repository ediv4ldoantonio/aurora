#pragma once

#include "Aurora/Scene/Components/Component.h"
#include "Aurora/Renderer/Material.h"
#include "Aurora/Renderer/RenderPass.h"

#include <memory>
#include <utility>
namespace Aurora
{

    struct SpriteComponent : public Component
    {
        SpriteComponent() = default;

        explicit SpriteComponent(
            std::shared_ptr<Material> material)
            : MaterialInstance(
                  std::move(material))
        {
        }

        std::shared_ptr<Material> MaterialInstance;

        int32_t Layer = 0;

        RenderPass Pass =
            RenderPass::World;
    };

}