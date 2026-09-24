#pragma once

#include <functional>
#include <utility>

namespace Aurora
{

    template <typename... Components>
    std::vector<Entity>
    View<Components...>::GetEntities()
    {

        std::vector<Entity> result;

        for (auto id :
             m_Registry->GetEntities())
        {

            Entity entity(
                id,
                m_Registry);

            if (
                HasAllComponents<Components...>(entity))
            {
                result.push_back(entity);
            }
        }

        return result;
    }

    template <typename... Components>
    template <typename Func>
    void View<Components...>::Each(Func &&func)
    {
        for (auto id : m_Registry->GetEntities())
        {
            Entity entity(
                id,
                m_Registry,
                m_Scene);

            if (HasAllComponents<Components...>(entity))
            {
                std::invoke(
                    std::forward<Func>(func),
                    entity,
                    entity.GetComponent<Components>()...);
            }
        }
    }

}