#pragma once

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

    private:
        Registry m_Registry;
        SystemManager m_SystemManager;
        std::vector<EntityID> m_DestroyQueue;
    };

}