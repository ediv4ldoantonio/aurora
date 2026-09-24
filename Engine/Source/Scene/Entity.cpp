#include "Aurora/ECS/Registry.h"
#include "Aurora/Scene/Scene.h"
#include "Aurora/Scene/Entity.h"
#include "Aurora/Scene/Components/RelationshipComponent.h"

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

    Entity Entity::GetParent() const
    {
        if (!IsValid() || !m_Registry->HasComponent<RelationshipComponent>(m_ID))
            return {};

        return m_Registry->GetComponent<RelationshipComponent>(m_ID).Parent;
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