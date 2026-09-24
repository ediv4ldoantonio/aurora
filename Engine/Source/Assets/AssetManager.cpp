#include "Aurora/Assets/AssetManager.h"
#include "Aurora/Core/Logger.h"

namespace Aurora
{
    bool AssetManager::Unload(const std::string &key)
    {
        return m_Assets.erase(key) > 0;
    }

    void AssetManager::Clear()
    {
        if (!m_Assets.empty())
            AURORA_LOG_TRACE("AssetManager: releasing {} asset(s)", m_Assets.size());
        m_Assets.clear();
    }
}
