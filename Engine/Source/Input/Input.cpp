#include "Aurora/Input/Input.h"
#include "Aurora/Input/KeyCodes.h"
#include "Aurora/Events/KeyEvents.h"
#include "Aurora/Events/MouseEvents.h"
#include "Aurora/Events/Event.h"
#include "Aurora/Events/EventDispatcher.h"

#include <cstring>
#include <array>
#include <vector>

namespace Aurora
{
    namespace
    {
        struct InputState
        {
            std::array<
                std::vector<KeyCode>,
                static_cast<size_t>(InputAction::ActionCount)>
                s_ActionBindings;

            std::array<bool, KeyCodeCount> Down{};
            std::array<bool, KeyCodeCount> Pressed{};
            std::array<bool, KeyCodeCount> Released{};

            std::array<bool, MouseButtonCount> MouseDown{};
            std::array<bool, MouseButtonCount> MousePressed{};
            std::array<bool, MouseButtonCount> MouseReleased{};

            Vector2 MousePosition{};
            Vector2 MouseScrollDelta{};
        };

        InputState s_State;

        bool InRange(KeyCode key)
        {
            return static_cast<uint16_t>(key) < KeyCodeCount;
        }

        bool InRange(MouseButton button)
        {
            return static_cast<size_t>(button) < MouseButtonCount;
        }
    }

    bool Input::IsKeyDown(KeyCode key)
    {
        return InRange(key) && s_State.Down[static_cast<size_t>(key)];
    }

    bool Input::IsKeyPressed(KeyCode key)
    {
        return InRange(key) && s_State.Pressed[static_cast<size_t>(key)];
    }

    bool Input::IsKeyReleased(KeyCode key)
    {
        return InRange(key) && s_State.Released[static_cast<size_t>(key)];
    }

    bool Input::IsMouseButtonDown(MouseButton button)
    {
        return InRange(button) &&
               s_State.MouseDown[static_cast<size_t>(button)];
    }

    bool Input::IsMouseButtonPressed(MouseButton button)
    {
        return InRange(button) &&
               s_State.MousePressed[static_cast<size_t>(button)];
    }

    bool Input::IsMouseButtonReleased(MouseButton button)
    {
        return InRange(button) &&
               s_State.MouseReleased[static_cast<size_t>(button)];
    }

    Vector2 Input::GetMousePosition()
    {
        return s_State.MousePosition;
    }

    Vector2 Input::GetMouseScrollDelta()
    {
        return s_State.MouseScrollDelta;
    }

    void Input::ProcessEvent(
        Event &event)
    {

        EventDispatcher dispatcher(event);

        dispatcher.Dispatch<KeyPressedEvent>(
            [](KeyPressedEvent &e)
            {
                if (!InRange(e.GetKeyCode()) || e.IsRepeat())
                    return false;

                const auto idx = static_cast<size_t>(e.GetKeyCode());

                s_State.Down[idx] = true;
                s_State.Pressed[idx] = true;

                return true;
            });

        dispatcher.Dispatch<KeyReleasedEvent>(
            [](KeyReleasedEvent &e)
            {
                if (!InRange(e.GetKeyCode()))
                    return false;

                const auto idx = static_cast<size_t>(e.GetKeyCode());

                s_State.Down[idx] = false;
                s_State.Released[idx] = true;
                return true;
            });

        dispatcher.Dispatch<MouseButtonPressedEvent>(
            [](MouseButtonPressedEvent &e)
            {
                if (!InRange(e.GetMouseButton()))
                    return false;

                const auto idx =
                    static_cast<size_t>(e.GetMouseButton());

                s_State.MouseDown[idx] = true;
                s_State.MousePressed[idx] = true;

                return true;
            });

        dispatcher.Dispatch<MouseButtonReleasedEvent>(
            [](MouseButtonReleasedEvent &e)
            {
                if (!InRange(e.GetMouseButton()))
                    return false;

                const auto idx =
                    static_cast<size_t>(e.GetMouseButton());

                s_State.MouseDown[idx] = false;
                s_State.MouseReleased[idx] = true;

                return true;
            });

        dispatcher.Dispatch<MouseMovedEvent>(
            [](MouseMovedEvent &e)
            {
                s_State.MousePosition =
                    e.GetPosition();

                return true;
            });

        dispatcher.Dispatch<MouseScrolledEvent>(
            [](MouseScrolledEvent &e)
            {
                s_State.MouseScrollDelta += e.GetOffset();
                return true;
            });
    }

    void Input::EndFrame()
    {
        s_State.Pressed.fill(false);
        s_State.Released.fill(false);

        s_State.MousePressed.fill(false);
        s_State.MouseReleased.fill(false);

        s_State.MouseScrollDelta = {};
    }

    void Input::Reset()
    {
        s_State = InputState{};
    }

    void Input::BindAction(
        InputAction action,
        KeyCode key)
    {
        auto &bindings =
            s_State.s_ActionBindings[static_cast<size_t>(action)];

        for (const auto boundKey : bindings)
        {
            if (boundKey == key)
                return;
        }

        bindings.push_back(key);
    }

    void Input::ClearActionBindings(
        InputAction action)
    {
        s_State.s_ActionBindings[static_cast<size_t>(action)].clear();
    }

    bool Input::IsActionDown(
        InputAction action)
    {
        const auto &bindings =
            s_State.s_ActionBindings[static_cast<size_t>(action)];

        for (const auto key : bindings)
        {
            if (IsKeyDown(key))
                return true;
        }

        return false;
    }

    bool Input::IsActionPressed(
        InputAction action)
    {
        const auto &bindings =
            s_State.s_ActionBindings[static_cast<size_t>(action)];

        for (const auto key : bindings)
        {
            if (IsKeyPressed(key))
                return true;
        }

        return false;
    }

    bool Input::IsActionReleased(
        InputAction action)
    {
        const auto &bindings =
            s_State.s_ActionBindings[static_cast<size_t>(action)];

        for (const auto key : bindings)
        {
            if (IsKeyReleased(key))
                return true;
        }

        return false;
    }
}