#pragma once

#include <cstdint>
#include <cstddef>
#include <functional>

namespace Aurora
{

    class UUID
    {
    public:
        UUID();

        explicit UUID(uint64_t uuid);

        operator uint64_t() const
        {
            return m_UUID;
        }

    private:
        uint64_t m_UUID;
    };

}

namespace std
{
    template <>
    struct hash<Aurora::UUID>
    {
        size_t operator()(const Aurora::UUID &uuid) const noexcept
        {
            return hash<uint64_t>{}(uuid);
        }
    };
}