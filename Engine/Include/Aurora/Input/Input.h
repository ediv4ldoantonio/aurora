#pragma once

#include "KeyCodes.h"
#include "Aurora/Events/Event.h"

namespace Aurora
{

    class Input
    {

    public:
        static bool IsKeyPressed(KeyCode key);

        static bool IsKeyDown(KeyCode key);

        static bool IsKeyReleased(KeyCode key);

        static void SetKey(
            KeyCode key,
            bool pressed);

        static void Update();

        static void ProcessEvent(
            Event &event);

        static void EndFrame();

        static void Reset();

    private:
        static bool s_CurrentKeys[512];

        static bool s_PreviousKeys[512];
    };

}