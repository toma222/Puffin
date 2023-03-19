
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
        }
    };
} // namespace editor
