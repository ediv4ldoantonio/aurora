#pragma once

#include "Aurora/Core/UUID.h"

#include <string>
#include <utility>

namespace Aurora
{
    enum class AssetType
    {
        None = 0,
        Texture2D,
        Shader
    };

    class Asset
    {
    public:
        virtual ~Asset() = default;

        Asset(const Asset &) = delete;
        Asset &operator=(const Asset &) = delete;

        virtual AssetType GetType() const = 0;

        // Source path (empty for assets created from memory).
        const std::string &GetPath() const { return m_Path; }
        const UUID &GetID() const { return m_ID; }

    protected:
        explicit Asset(std::string path = {}) : m_Path(std::move(path)) {}

    private:
        std::string m_Path;
        UUID m_ID;
    };
}
