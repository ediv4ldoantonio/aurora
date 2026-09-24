#pragma once

#include "Aurora/Assets/Asset.h"

#include <memory>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <utility>

namespace Aurora
{
    // Owns assets. Everyone else (renderer, components, scripts) holds non-owning pointers.
    //
    // Assets are addressed by a string key. For assets loaded from disk the key is the path.
    // An asset type T must provide:  static std::shared_ptr<T> T::Create(const std::string& path)
    class AssetManager
    {
    public:
        AssetManager() = default;
        ~AssetManager() { Clear(); }

        AssetManager(const AssetManager &) = delete;
        AssetManager &operator=(const AssetManager &) = delete;

        // Returns the cached asset for `path`, loading it first if necessary.
        // Returns nullptr if loading fails or if the key is used by an asset of another type.
        template <typename T>
        T *Load(const std::string &path)
        {
            static_assert(std::is_base_of_v<Asset, T>, "T must derive from Asset");

            if (auto it = m_Assets.find(path); it != m_Assets.end())
                return dynamic_cast<T *>(it->second.get());

            std::shared_ptr<T> asset = T::Create(path);
            if (!asset)
                return nullptr;

            T *raw = asset.get();
            m_Assets.emplace(path, std::move(asset));
            return raw;
        }

        // Registers an already-created asset under `key`. Replaces any existing asset with that key.
        template <typename T>
        T *Add(const std::string &key, std::shared_ptr<T> asset)
        {
            static_assert(std::is_base_of_v<Asset, T>, "T must derive from Asset");
            if (!asset)
                return nullptr;

            T *raw = asset.get();
            m_Assets[key] = std::move(asset);
            return raw;
        }

        // Returns a previously loaded/added asset or nullptr.
        template <typename T>
        T *Get(const std::string &key) const
        {
            static_assert(std::is_base_of_v<Asset, T>, "T must derive from Asset");
            auto it = m_Assets.find(key);
            return it == m_Assets.end() ? nullptr : dynamic_cast<T *>(it->second.get());
        }

        bool Has(const std::string &key) const { return m_Assets.contains(key); }
        bool Unload(const std::string &key);
        void Clear();
        size_t Count() const { return m_Assets.size(); }

    private:
        std::unordered_map<std::string, std::shared_ptr<Asset>> m_Assets;
    };
}
