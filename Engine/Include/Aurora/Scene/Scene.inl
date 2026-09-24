#pragma once

#include "Aurora/Scene/Scene.h"

namespace Aurora
{

    template <typename... Components>
    View<Components...> Scene::GetAllEntitiesWith()
    {
        return View<Components...>(&m_Registry, this);
    }

}