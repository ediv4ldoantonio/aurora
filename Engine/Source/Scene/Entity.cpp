#include "Aurora/ECS/Registry.h"
#include "Aurora/Scene/Scene.h"
#include "Aurora/Scene/Entity.h"

namespace Aurora
{

    Entity::Entity(
        EntityID id,
        Registry *registry,
        Scene *scene)
        : m_ID(id),
          m_Registry(registry),
          m_Scene(scene)
    {
    }

    bool Entity::IsValid() const
    {
        return m_Registry != nullptr &&
               m_Scene != nullptr;
    }

    void Entity::Destroy()
    {
        if (!IsValid())
            return;

        if (m_Registry->IsPendingDestroy(m_ID))
            return;

        m_Registry->MarkPendingDestroy(m_ID);

        m_Scene->DestroyEntity(*this);
    }

}