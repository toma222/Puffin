
#pragma once

#include "puffin/core/Base.h"
#include "puffin/core/Logging.h"

namespace PN
{
    enum PUFFIN_API EventType
    {
        KEYDOWN,
        MOUSEMOVE
    };

    class PUFFIN_API Event
    {
    private:
        const static EventType m_type;

    public:
        ~Event()
        {
            return;
        }

        EventType GetType() { return m_type; };

        bool Handled;
    };

    class PUFFIN_API EventDispatcher
    {
    private:
        Event *m_event;

    public:
        EventDispatcher(Event *e)
        {
            e = m_event;
        }

        // T is event class, F is the function to call
        // @param func must be a funtion that takes in event and return bool
        template <typename T, typename F>
        bool Dispatch(const F &func)
        {
            // Check if the classes are the same
            if (m_event->GetType() = T::GetStaticType(static_cast<T *>(m_event)))
            {
                // Call the function
                m_event->Handled |= func(m_event);
                return true;
            }

            return false;
        }

        ~EventDispatcher();
    };
} // namespace PN
