#pragma once

namespace Aurora
{

    template <typename T>
    ComponentPool<T> &Registry::GetPool()
    {
        auto type =
            GetComponentTypeID<T>();

        auto iterator =
            m_ComponentPools.find(type);

        if (iterator == m_ComponentPools.end())
        {

            auto pool =
                std::make_unique<ComponentPool<T>>();

            auto *result =
                pool.get();

            m_ComponentPools[type] =
                std::move(pool);

            return *result;
        }

        return *static_cast<ComponentPool<T> *>(
            iterator->second.get());
    }

    template <typename T, typename... Args>
    T &Registry::AddComponent(
        EntityID entity,
        Args &&...args)
    {

        auto &pool =
            GetPool<T>();

        return pool.Add(
            entity,
            std::forward<Args>(args)...);
    }

    template <typename T>
    T &Registry::GetComponent(
        EntityID entity)
    {

        auto &pool =
            GetPool<T>();

        return pool.Get(entity);
    }

    template <typename T>
    bool Registry::HasComponent(
        EntityID entity)
    {

        auto &pool =
            GetPool<T>();

        return pool.Has(entity);
    }

    template <typename... Components>
    View<Components...>
    Registry::ViewEntities()
    {

        return View<Components...>(
            this, m_Scene);
    }

}