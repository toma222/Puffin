
#include "SDL.h"
#include "Math/PNVector.h"

namespace puffin
{
    struct SDLRectWrapper
    {
    public:
        SDLRectWrapper(int x = 0, int y = 0, int w = 0, int h = 0)
        {
            m_rect = new SDL_Rect({x, y, w, h});
        }

        SDL_Rect *m_rect;

        int x()
        {
            return m_rect->x;
        }

        int y()
        {
            return m_rect->y;
        }

        int w()
        {
            return m_rect->w;
        }

        int h()
        {
            return m_rect->h;
        }

        ~SDLRectWrapper()
        {
            delete m_rect;
        }
    };

} // namespace puffin
