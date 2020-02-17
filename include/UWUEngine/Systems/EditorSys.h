#pragma once

#include <UWUEngine/System.h>
#include <imgui.h>
#include <string>
#include <UWUEngine/Editors/WindowManager.h>

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
    Editors::WindowManager windowManager;

    //Function
    void ToggleActivate();

    //Snippets
    void DockSpace() const;
    void MainMenu();
    static void PopUpSaveAs();
  };
}
