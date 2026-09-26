#include "Aurora/Input/InputActionMap.h"

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
}