
#pragma once

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_sdl.h"
#include "imgui/backends/imgui_impl_sdlrenderer.h"

#include "Rendering/PWindow.h"
#include "Rendering/PRenderer.h"

namespace puffin
{
    class Gui
    {
    public:
        virtual void UpdateGUI(render::SDLTexture *renderTexture) { return; };
        virtual void StartGUI(render::SDLWindow *window, render::SDLRenderer *renderer) { return; };
    };
} // namespace puffin
