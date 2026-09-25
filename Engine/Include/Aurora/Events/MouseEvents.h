#pragma once

#include "Event.h"
#include "Aurora/Input/MouseCodes.h"

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
}