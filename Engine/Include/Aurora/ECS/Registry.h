#pragma once

#include <unordered_map>
#include <memory>
#include <vector>
#include <unordered_set>

#include "Aurora/Scene/Entity.h"
#include "Aurora/ECS/ComponentPool.h"
#include "Aurora/ECS/Component.h"
#include "Aurora/ECS/View.h"

namespace Aurora
{
    class Scene;

    class Registry
    {

    public:
        Entity CreateEntity(Scene *scene);

        template <typename T, typename... Args>
        T &AddComponent(
            EntityID entity,
            Args &&...args);

        template <typename T>
        T &GetComponent(
            EntityID entity);

        template <typename T>
        bool HasComponent(
            EntityID entity);

        template <typename... Components>
        View<Components...> ViewEntities();

        const std::vector<EntityID> &GetEntities() const;

        bool IsPendingDestroy(EntityID entity) const;

        void MarkPendingDestroy(EntityID entity);

        void ClearPendingDestroy(EntityID entity);

        void DestroyEntity(EntityID entity);

    private:
        template <typename T>
        ComponentPool<T> &GetPool();

    private:
        EntityID m_NextEntityID = 1;

        std::vector<EntityID> m_Entities;

        std::unordered_map<
            ComponentType,
            std::unique_ptr<IComponentPool>>
            m_ComponentPools;

        std::unordered_set<EntityID> m_PendingDestroy;
    };

}

#include "Aurora/ECS/Registry.inl"
#include "Aurora/Scene/Entity.inl"
#include "Aurora/ECS/View.inl"
