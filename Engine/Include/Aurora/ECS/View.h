#pragma once

#include <vector>

#include "Aurora/Scene/Entity.h"

namespace Aurora
{

    template <typename... Components>
    class View
    {

    public:
        View(
            Registry *registry,
            Scene *scene = nullptr)
            : m_Registry(registry),
              m_Scene(scene)
        {
        }

        std::vector<Entity> GetEntities();

    private:
        template <typename... Required>
        bool HasAllComponents(Entity entity)
        {
            return (
                entity.HasComponent<Required>() && ...);
        }

    private:
        Registry *m_Registry = nullptr;
        Scene *m_Scene = nullptr;
    };

}
