
#include "puffin/core/Base.h"
#include "puffin/core/Logging.h"
#include "Event.h"

namespace PN
{
    class MouseEvent : public Event
    {
    private:
        const static EventType m_type = MOUSEMOVE;

        int m_mouseX;
        int m_mouseY;

    public:
        static EventType GetStaticType() { return m_type; }

        EventType GetEventType() const override { return m_type; };

        MouseEvent(int X, int Y) : m_mouseX(X), m_mouseY(Y){};

        int GetMouseX() { return m_mouseX; };
        int GetMouseY() { return m_mouseY; };
    };
} // namespace PN
