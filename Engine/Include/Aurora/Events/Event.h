#pragma once

#include <string>

namespace Aurora
{

    enum class EventType
    {
        None = 0,

        WindowClose,
        WindowResize,

        KeyPressed,
        KeyReleased,

        MouseButtonPressed,
        MouseButtonReleased,
        MouseMoved,
    };

    enum EventCategory
    {
        EventCategoryNone = 0,

        EventCategoryApplication = 1 << 0,
        EventCategoryInput = 1 << 1,
        EventCategoryKeyboard = 1 << 2,
        EventCategoryMouse = 1 << 3
    };

    class Event
    {

    public:
        virtual ~Event() = default;

        virtual EventType GetEventType() const = 0;

        virtual const char *GetName() const = 0;

        bool Handled = false;

        virtual int GetCategoryFlags() const = 0;

        bool IsInCategory(EventCategory category)
        {
            return GetCategoryFlags() & category;
        }
    };

}

#define EVENT_CLASS_TYPE(type)                      \
    static EventType GetStaticType()                \
    {                                               \
        return EventType::type;                     \
    }                                               \
    virtual EventType GetEventType() const override \
    {                                               \
        return GetStaticType();                     \
    }                                               \
    virtual const char *GetName() const override    \
    {                                               \
        return #type;                               \
    }

#define EVENT_CLASS_CATEGORY(category)            \
    virtual int GetCategoryFlags() const override \
    {                                             \
        return category;                          \
    }
