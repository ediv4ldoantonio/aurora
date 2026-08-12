#include "Aurora/ECS/Registry.h"

#include <vector>
#include <algorithm>

namespace Aurora
{

    Entity Registry::CreateEntity(Scene *scene)
    {

        EntityID id =
            m_NextEntityID++;

        m_Entities.push_back(id);

        return Entity(
            id,
            this,
            scene);
    }

    const std::vector<EntityID> &Registry::GetEntities() const
    {
        return m_Entities;
    }

    void Registry::MarkPendingDestroy(EntityID entity)
    {
        m_PendingDestroy.insert(entity);
    }

    bool Registry::IsPendingDestroy(EntityID entity) const
    {
        return m_PendingDestroy.contains(entity);
    }

    void Registry::ClearPendingDestroy(EntityID entity)
    {
        m_PendingDestroy.erase(entity);
    }

    void Registry::DestroyEntity(EntityID entity)
    {
        for (auto &[type, pool] : m_ComponentPools)
            pool->Remove(entity);

        std::erase(m_Entities, entity);

        m_PendingDestroy.erase(entity);
    }
}