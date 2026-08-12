#pragma once

#include <utility>

#include "Aurora/ECS/Registry.h"
#include "Aurora/Scene/Scene.h"

namespace Aurora
{

    template <typename T, typename... Args>
    T &Entity::AddComponent(
        Args &&...args)
    {

        return m_Registry->template AddComponent<T>(
            m_ID,
            std::forward<Args>(args)...);
    }

    template <typename T>
    T &Entity::GetComponent()
    {

        return m_Registry->template GetComponent<T>(
            m_ID);
    }

    template <typename T>
    bool Entity::HasComponent()
    {

        return m_Registry->template HasComponent<T>(
            m_ID);
    }

}