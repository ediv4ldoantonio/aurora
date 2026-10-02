#include "Aurora/Input/InputActionMap.h"

#include <fstream>

namespace Aurora
{
    void InputActionMap::Bind(
        InputAction action,
        KeyCode key)
    {
        auto &bindings =
            m_Bindings[static_cast<size_t>(action)];

        for (const auto boundKey : bindings)
        {
            if (boundKey == key)
                return;
        }

        bindings.push_back(key);
    }

    void InputActionMap::Rebind(
        InputAction action,
        KeyCode key)
    {
        Clear(action);
        Bind(action, key);
    }

    void InputActionMap::Clear(
        InputAction action)
    {
        m_Bindings[static_cast<size_t>(action)].clear();
    }

    const std::vector<KeyCode> &
    InputActionMap::GetBindings(
        InputAction action) const
    {
        return m_Bindings[static_cast<size_t>(action)];
    }

    bool InputActionMap::SaveToFile(
        const std::string &path) const
    {
        std::ofstream file(path);

        if (!file)
            return false;

        for (size_t actionIndex = 0;
             actionIndex <
             static_cast<size_t>(InputAction::ActionCount);
             ++actionIndex)
        {
            const auto &bindings =
                m_Bindings[actionIndex];

            for (const auto key : bindings)
            {
                file
                    << actionIndex
                    << ' '
                    << static_cast<uint16_t>(key)
                    << '\n';
            }
        }

        return true;
    }

    bool InputActionMap::LoadFromFile(
        const std::string &path)
    {
        std::ifstream file(path);

        if (!file)
            return false;

        std::array<
            std::vector<KeyCode>,
            static_cast<size_t>(InputAction::ActionCount)>
            loadedBindings;

        size_t actionIndex = 0;
        uint16_t keyValue = 0;

        while (file >> actionIndex >> keyValue)
        {
            if (actionIndex >=
                static_cast<size_t>(
                    InputAction::ActionCount))
            {
                continue;
            }

            if (keyValue >= KeyCodeCount)
            {
                continue;
            }

            auto &bindings =
                loadedBindings[actionIndex];

            const auto key =
                static_cast<KeyCode>(keyValue);

            bool alreadyBound = false;

            for (const auto boundKey : bindings)
            {
                if (boundKey == key)
                {
                    alreadyBound = true;
                    break;
                }
            }

            if (!alreadyBound)
            {
                bindings.push_back(key);
            }
        }

        m_Bindings =
            std::move(loadedBindings);

        return true;
    }
}