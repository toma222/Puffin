
#pragma once

#include "puffin/core/Base.h"
#include "puffin/core/Logging.h"

namespace PN
{
    enum EventType
    {
        KEYBOARD,
        MOUSE
    };

    class Event
    {
    private:
        EventType m_type;

    public:
        Event(EventType type);
        ~Event();

        void Dispach();
    };

    Event::Event(EventType type)
    {
        m_type = type;
    }
} // namespace PN
