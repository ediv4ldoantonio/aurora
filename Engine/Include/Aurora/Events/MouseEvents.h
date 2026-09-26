#pragma once

#include "Aurora/Math/Vector2.h"
#include "Aurora/Input/MouseCodes.h"

#include "Event.h"
namespace Aurora
{
    class MouseButtonPressedEvent : public Event
    {
    public:
        MouseButtonPressedEvent(
            MouseButton button)
            : m_MouseButton(button)
        {
        }

        MouseButton GetMouseButton() const
        {
            return m_MouseButton;
        }

        EVENT_CLASS_TYPE(MouseButtonPressed)

        EVENT_CLASS_CATEGORY(
            EventCategoryMouse |
            EventCategoryInput)

    private:
        MouseButton m_MouseButton;
    };

    class MouseButtonReleasedEvent : public Event
    {
    public:
        MouseButtonReleasedEvent(
            MouseButton button)
            : m_MouseButton(button)
        {
        }

        MouseButton GetMouseButton() const
        {
            return m_MouseButton;
        }

        EVENT_CLASS_TYPE(MouseButtonReleased)

        EVENT_CLASS_CATEGORY(
            EventCategoryMouse |
            EventCategoryInput)

    private:
        MouseButton m_MouseButton;
    };

    class MouseMovedEvent : public Event
    {
    public:
        MouseMovedEvent(
            const Vector2 &position)
            : m_Position(position)
        {
        }

        const Vector2 &GetPosition() const
        {
            return m_Position;
        }

        EVENT_CLASS_TYPE(MouseMoved)

        EVENT_CLASS_CATEGORY(
            EventCategoryMouse |
            EventCategoryInput)

    private:
        Vector2 m_Position;
    };
}