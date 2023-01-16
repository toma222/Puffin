
#pragma once

#include <puffin.h>

#include <vector>
#include <memory>

#include "editorGUI.h"

namespace editor
{
    class EditorApplication : public puffin::Application
    {
    private:
        editorGUI *m_gui;

    public:
        void SetEditorGUI()
        {
            m_gui = new editorGUI();
        }

        void CleanEditor()
        {
            delete m_gui;
        }

        void StartApplication() override
        {
            bool open = true;

            m_gui->StartGUI(m_window->GetWindow(), m_graphics->GetRenderer().get());
            m_layerStack->AttachLayers();

            while (open == true)
            {
                // poll for events

                SDL_Event e;
                while (SDL_PollEvent(&e) > 0)
                {
                    ImGui_ImplSDL2_ProcessEvent(&e);

                    switch (e.type)
                    {
                    case SDL_QUIT:
                        open = false;
                        break;
                    }
                }

                m_graphics->ClearRenderer();
                m_layerStack->UpdateLayers();
                m_graphics->RenderTextures();

                m_gui->UpdateGUI(m_graphics->GetRenderTexture().get());
                m_graphics->RenderPresent();
                m_window->UpdateWindow();
            }

            m_layerStack->DetachLayers();
        }
    };
} // namespace editor
