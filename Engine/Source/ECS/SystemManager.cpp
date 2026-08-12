#include "Aurora/ECS/SystemManager.h"

namespace Aurora
{

    void SystemManager::Update(
        Registry &registry,
        float dt)
    {

        for (auto &system : m_Systems)
        {

            system->OnUpdate(
                registry,
                dt);
        }
    }

    void SystemManager::Render(
        Registry &registry)
    {

        for (auto &system : m_Systems)
        {

            system->OnRender(
                registry);
        }
    }

}