#pragma once

#include "Aurora/Input/KeyCodes.h"
#include <array>
#include <cstdint>
#include <vector>

namespace Aurora
{
    enum class InputAction : uint8_t
    {
        MoveUp = 0,
        MoveDown,
        MoveLeft,
        MoveRight,
        Jump,
        ActionCount
    };

    class InputActionMap
    {
    public:
        void Bind(
            InputAction action,
            KeyCode key);

        void Clear(
            InputAction action);

        const std::vector<KeyCode> &GetBindings(
            InputAction action) const;

    private:
        std::array<
            std::vector<KeyCode>,
            static_cast<size_t>(InputAction::ActionCount)>
            m_Bindings;
    };
}