#pragma once

#include "Aurora/Events/Event.h"

namespace Aurora
{

    class WindowCloseEvent : public Event
    {

    public:
        EVENT_CLASS_TYPE(WindowClose)
        EVENT_CLASS_CATEGORY(
            EventCategoryApplication)
    };

    class WindowResizeEvent : public Event
    {

    public:
        WindowResizeEvent(
            unsigned int width,
            unsigned int height)
            : width(width),
              height(height)
        {
        }

        unsigned int GetWidth()
        {
            return width;
        }

        unsigned int GetHeight()
        {
            return height;
        }

        EVENT_CLASS_TYPE(WindowResize)
        EVENT_CLASS_CATEGORY(
            EventCategoryApplication)
    private:
        unsigned int width;
        unsigned int height;
    };

}