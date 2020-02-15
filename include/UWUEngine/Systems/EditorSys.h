#pragma once

#include <UWUEngine/System.h>
#include <imgui.h>
#include <string>

namespace UWUEngine
{
  class EditorSys : public System
  {
  public:
    EditorSys(ISpace* p);
    ~EditorSys() override;

    void Update() override;

    bool IsActive() const;

  private:
    //Data
    bool isActive;

    //Function
    void ToggleActivate();

    //Helpers
    static void HelpMarker(const char* desc);
    static bool InputText(const char* label, std::string* str, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL, void* user_data = NULL);
    static bool InputTextMultiline(const char* label, std::string* str, const ImVec2& size = ImVec2(0, 0), ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL, void* user_data = NULL);
    static bool InputTextWithHint(const char* label, const char* hint, std::string* str, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL, void* user_data = NULL);

    //Snippets
    void DockSpace() const;
    void MainMenu();
    static void PopUpSaveAs();
  };
}
