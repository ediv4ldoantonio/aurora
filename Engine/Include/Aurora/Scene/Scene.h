#pragma once

#include <unordered_map>
#include <string>
#include <vector>

#include "Aurora/Core/UUID.h"
#include "Aurora/ECS/Registry.h"
#include "Aurora/ECS/SystemManager.h"

namespace Aurora
{

    class Scene
    {

    public:
        Scene();
        Entity CreateEntity(const std::string &name = "Entity");

        void OnUpdate(
            float deltaTime);

        void OnRender();

        void SetParent(
            Entity child,
            Entity parent);

        void RemoveParent(
            Entity child);

        void DestroyEntity(Entity entity);

        void ProcessDestroyQueue();

        void DestroyEntityNow(
            Entity entity);

        Entity GetEntityByUUID(UUID uuid);

    private:
        Registry m_Registry;
        SystemManager m_SystemManager;
        std::unordered_map<Aurora::UUID, EntityID> m_EntityMap;
        std::vector<EntityID> m_DestroyQueue;
    };

}