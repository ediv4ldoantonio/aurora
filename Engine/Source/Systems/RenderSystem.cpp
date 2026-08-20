#include "Aurora/Scene/Components/TransformComponent.h"
#include "Aurora/Scene/Components/SpriteComponent.h"
#include "Aurora/Renderer/Renderer2D.h"
#include "Aurora/ECS/Registry.h"
#include "Aurora/Systems/RenderSystem.h"

namespace Aurora
{

    void RenderSystem::OnRender(
        Registry &registry)
    {
        Renderer2D::BeginFrame();

        auto view =
            registry.ViewEntities<
                TransformComponent,
                SpriteComponent>();

        for (auto entity :
             view.GetEntities())
        {
            auto &transform =
                entity.GetComponent<TransformComponent>();

            auto &sprite =
                entity.GetComponent<SpriteComponent>();

            Renderer2D::DrawSprite(
                transform,
                sprite);
        }

        Renderer2D::EndFrame();
    }

}