#pragma once

#include "Aurora/Events/Event.h"
#include "Aurora/Math/Vector2.h"

#include "InputActionMap.h"
#include "KeyCodes.h"
#include "MouseCodes.h"

#include <cstdint>

namespace Aurora
{
    class Input
    {

    public:
        static bool IsKeyPressed(KeyCode key);
        static bool IsKeyDown(KeyCode key);
        static bool IsKeyReleased(KeyCode key);

        static void ProcessEvent(
            Event &event);

        static void EndFrame();

        static void Reset();

        static bool IsMouseButtonPressed(MouseButton button);
        static bool IsMouseButtonDown(MouseButton button);
        static bool IsMouseButtonReleased(MouseButton button);

        static Vector2 GetMousePosition();
        static Vector2 GetMouseScrollDelta();

        static void BindAction(
            InputAction action,
            KeyCode key);

        static void ClearActionBindings(
            InputAction action);

        static bool IsActionDown(
            InputAction action);

        static bool IsActionPressed(
            InputAction action);

        static bool IsActionReleased(
            InputAction action);

        static void SetupDefaultBindings();
    };

}