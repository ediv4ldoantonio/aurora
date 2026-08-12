#pragma once

#include <cstdint>

namespace Aurora
{

    using EntityID = uint32_t;

    class Registry;

    class Scene;

    class Entity
    {

    public:
        Entity() = default;

        Entity(
            EntityID id,
            Registry *registry,
            Scene *scene = nullptr);

        EntityID GetID() const
        {
            return m_ID;
        }

        bool IsValid() const;

        template <typename T, typename... Args>
        T &AddComponent(
            Args &&...args);

        template <typename T>
        T &GetComponent();

        template <typename T>
        bool HasComponent();

        operator bool() const
        {
            return IsValid();
        }

        bool operator==(const Entity &other) const
        {
            return m_ID == other.m_ID &&
                   m_Registry == other.m_Registry;
        }

        bool operator!=(const Entity &other) const
        {
            return !(*this == other);
        }

        void Destroy();

    private:
        EntityID m_ID = 0;

        Registry *m_Registry = nullptr;

        Scene *m_Scene;
    };

}