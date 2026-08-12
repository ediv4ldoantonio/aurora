#pragma once

#include <unordered_map>
#include <utility>
#include <algorithm>

namespace Aurora
{

    class IComponentPool
    {

    public:
        virtual ~IComponentPool() = default;
        virtual void Remove(EntityID entity) = 0;
    };

    template <typename T>
    class ComponentPool : public IComponentPool
    {

    public:
        template <typename... Args>
        T &Add(
            EntityID entity,
            Args &&...args)
        {

            auto [it, inserted] =
                m_Data.emplace(
                    entity,
                    T(std::forward<Args>(args)...));

            if (inserted)
                m_Entities.push_back(entity);

            return it->second;
        }

        T &Get(
            EntityID entity)
        {

            return m_Data.at(entity);
        }

        bool Has(
            EntityID entity) const
        {

            return m_Data.contains(entity);
        }

        void Remove(EntityID entity) override
        {
            m_Data.erase(entity);

            auto it = std::find(
                m_Entities.begin(),
                m_Entities.end(),
                entity);

            if (it != m_Entities.end())
                m_Entities.erase(it);
        }

    private:
        std::unordered_map<EntityID, T> m_Data;

        std::vector<EntityID> m_Entities;
    };

}