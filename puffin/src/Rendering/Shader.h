
#pragma once

#include <functional>

#include "Math/PNVector.h"

namespace puffin
{
    class PixelShader
    {
    public:
        std::function<PNColor(int, int, PNColor)> m_FragReference;
    };

    class TextureShader
    {
    public:
    };

    // ---------------- BASIC OUT THE BOX SHADER ---------------- //
    PNColor PalletPixelShader(int x, int y, PNColor color);

} // namespace puffin
