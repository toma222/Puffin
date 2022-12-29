
#pragma once

#include "puffin/core/Base.h"
#include "puffin/core/Logging.h"

#include "Event.h"

namespace PN
{
    class PUFFIN_API KeyDown : public Event
    {
        // const static EventType m_type = KEYDOWN;

    public:
        static EventType GetStaticType() { return KEYDOWN; }

    private:
    };
} // namespace PN
