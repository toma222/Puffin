
#include <SDL2/SDL.h>

namespace puffin
{
    class Input
    {
    public:
        static int m_mouseButton[3];

        static bool KeyDown(int ScanCode)
        {
            const Uint8 *kb = SDL_GetKeyboardState(NULL);
            return (bool)kb[ScanCode];
        }

        static bool KeyUp(int ScanCode)
        {
            const Uint8 *kb = SDL_GetKeyboardState(NULL);
            return !((bool)kb[ScanCode]);
        }

        static bool MouseDown(int mouseCode)
        {
            int x, y;
            const Uint32 ms = SDL_GetMouseState(&x, &y);
            return (bool)(ms & SDL_BUTTON(mouseCode));
        }
    };
} // namespace puffin
