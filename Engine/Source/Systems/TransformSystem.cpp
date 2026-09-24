#include "Aurora/Systems/TransformSystem.h"
#include "Aurora/Scene/Components/TransformComponent.h"
#include "Aurora/Scene/Components/RelationshipComponent.h"
#include "Aurora/ECS/Registry.h"
#include "Aurora/Core/Logger.h"

namespace Aurora
{
    void TransformSystem::OnUpdate(
        Registry &registry,
        float)
    {
        auto view =
            registry.ViewEntities<TransformComponent,
                                  RelationshipComponent>();

        for (auto entity : view.GetEntities())
        {
            auto &relationship =
                entity.GetComponent<RelationshipComponent>();

            if (!relationship.Parent)
                UpdateEntity(entity);
        }
    }

    void TransformSystem::UpdateEntity(Entity entity)
    {
        auto &transform =
            entity.GetComponent<TransformComponent>();

        auto &relationship =
            entity.GetComponent<RelationshipComponent>();

        if (relationship.Parent)
        {
            auto &parentTransform =
                relationship.Parent
                    .GetComponent<TransformComponent>();

            transform.WorldTransform.Position =
                parentTransform.WorldTransform.Position +
                transform.LocalTransform.Position;

            transform.WorldTransform.Rotation =
                parentTransform.WorldTransform.Rotation +
                transform.LocalTransform.Rotation;

            transform.WorldTransform.Scale =
                {parentTransform.WorldTransform.Scale.x *
                     transform.LocalTransform.Scale.x,
                 parentTransform.WorldTransform.Scale.y *
                     transform.LocalTransform.Scale.y};
        }
        else
        {
            transform.WorldTransform.Position =
                transform.LocalTransform.Position;

            transform.WorldTransform.Rotation =
                transform.LocalTransform.Rotation;

            transform.WorldTransform.Scale =
                transform.LocalTransform.Scale;
        }

        for (auto child : relationship.Children)
            UpdateEntity(child);
    }
}
