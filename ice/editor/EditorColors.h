
#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"

/* GENERALIZED_COLORS */

#define EditorText 0x212123
#define EditorBackground 0x212123

#define EditorTab1 0x45444f
#define EditorWindow1 0x646365
#define EditorScrollbar1 0xb8b5b9

#define EditorTab2 0x646365
#define EditorWindow2 0x868188
#define EditorScrollbar2 0xb8b5b9

#define ItemBackground 0xb8b5b9
#define ItemColor 0xf2f0e5

#define EditorOther1 0x45444f
#define EditorOther2 0x646365

namespace editor
{
    ImVec4 ImGuiConvertHex(Uint32 hexValue)
    {
        return ImVec4((double)((hexValue >> 16) & 0xFF) / 255,
                      (double)((hexValue >> 8) & 0xFF) / 255,
                      (double)((hexValue)&0xFF) / 255,
                      (double)255);
    }

    void ColorImGUI()
    {
        ImGuiStyle &style = ImGui::GetStyle();

        /*
        Missing
            - MenuBar
        */

        style.FrameRounding = 6;
        style.FramePadding = ImVec2(15, 6);
        style.ScrollbarRounding = (int)16;

        style.Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
        style.Colors[ImGuiCol_TextDisabled] = ImGuiConvertHex(EditorText);

        style.Colors[ImGuiCol_WindowBg] = ImGuiConvertHex(EditorBackground);

        style.Colors[ImGuiCol_ChildBg] = ImGuiConvertHex(EditorWindow1);
        style.Colors[ImGuiCol_PopupBg] = ImGuiConvertHex(EditorWindow1);
        style.Colors[ImGuiCol_Border] = ImGuiConvertHex(EditorTab1);
        style.Colors[ImGuiCol_BorderShadow] = ImGuiConvertHex(EditorTab1);
        style.Colors[ImGuiCol_FrameBg] = ImGuiConvertHex(EditorWindow1);
        style.Colors[ImGuiCol_FrameBgHovered] = ImGuiConvertHex(EditorWindow1);
        style.Colors[ImGuiCol_FrameBgActive] = ImGuiConvertHex(EditorWindow2);

        style.Colors[ImGuiCol_TitleBg] = ImGuiConvertHex(EditorTab1);
        style.Colors[ImGuiCol_TitleBgActive] = ImGuiConvertHex(EditorTab2);
        style.Colors[ImGuiCol_TitleBgCollapsed] = ImGuiConvertHex(EditorTab1);

        style.Colors[ImGuiCol_Tab] = ImGuiConvertHex(EditorTab1);
        style.Colors[ImGuiCol_TabHovered] = ImGuiConvertHex(EditorTab1);
        style.Colors[ImGuiCol_TabActive] = ImGuiConvertHex(EditorTab2);
        style.Colors[ImGuiCol_TabUnfocused] = ImGuiConvertHex(EditorTab1);
        style.Colors[ImGuiCol_TabUnfocusedActive] = ImGuiConvertHex(EditorTab1);

        style.Colors[ImGuiCol_NavHighlight] = ImGuiConvertHex(EditorTab1);
        style.Colors[ImGuiCol_NavWindowingHighlight] = ImGuiConvertHex(EditorTab1);
        style.Colors[ImGuiCol_NavWindowingDimBg] = ImGuiConvertHex(EditorTab1);
        style.Colors[ImGuiCol_ModalWindowDimBg] = ImGuiConvertHex(EditorTab1);

        style.Colors[ImGuiCol_ScrollbarBg] = ImGuiConvertHex(EditorTab1);
        style.Colors[ImGuiCol_ScrollbarGrab] = ImGuiConvertHex(EditorScrollbar1);
        style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImGuiConvertHex(EditorScrollbar2);
        style.Colors[ImGuiCol_ScrollbarGrabActive] = ImGuiConvertHex(EditorScrollbar2);

        style.Colors[ImGuiCol_CheckMark] = ImGuiConvertHex(EditorOther1);
        style.Colors[ImGuiCol_SliderGrab] = ImGuiConvertHex(EditorOther1);
        style.Colors[ImGuiCol_SliderGrabActive] = ImGuiConvertHex(EditorOther2);
        style.Colors[ImGuiCol_Button] = ImGuiConvertHex(EditorOther1);
        style.Colors[ImGuiCol_ButtonHovered] = ImGuiConvertHex(EditorOther1);
        style.Colors[ImGuiCol_ButtonActive] = ImGuiConvertHex(EditorOther2);
        style.Colors[ImGuiCol_Header] = ImGuiConvertHex(EditorOther1);
        style.Colors[ImGuiCol_HeaderHovered] = ImGuiConvertHex(EditorOther1);
        style.Colors[ImGuiCol_HeaderActive] = ImGuiConvertHex(EditorOther2);

        style.Colors[ImGuiCol_Separator] = ImGuiConvertHex(EditorTab1);
        style.Colors[ImGuiCol_SeparatorHovered] = ImGuiConvertHex(EditorTab2);
        style.Colors[ImGuiCol_SeparatorActive] = ImGuiConvertHex(EditorTab2);

        style.Colors[ImGuiCol_ResizeGrip] = ImGuiConvertHex(EditorTab1);
        style.Colors[ImGuiCol_ResizeGripHovered] = ImGuiConvertHex(EditorTab2);
        style.Colors[ImGuiCol_ResizeGripActive] = ImGuiConvertHex(EditorTab2);

        style.Colors[ImGuiCol_DockingPreview] = ImVec4(0, 0, 0, 0.7f);
        style.Colors[ImGuiCol_DockingEmptyBg] = ImVec4(0, 0, 0, 0.5f);

        style.Colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
        style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
        style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
        style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);

        style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
        style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f); // Prefer using Alpha=1.0 here
        style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);  // Prefer using Alpha=1.0 here
        style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);

        style.Colors[ImGuiCol_TextSelectedBg] = ImGuiConvertHex(EditorText);

        style.Colors[ImGuiCol_DragDropTarget] = ImGuiConvertHex(EditorTab2);

        style.FrameRounding = 1;
        style.FrameBorderSize = 1;

        style.WindowRounding = 0.25;
        style.WindowBorderSize = 1;
    }
} // namespace editor
