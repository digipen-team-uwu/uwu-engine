/******************************************************************************/
/*!
\par        Project Umbra
\file       EditorMainMenu.cpp
\author     Yi Qian
\date       2020/01/01
\brief      Editor's main menu and stuffs

Copyright © 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#include <UWUEngine/Editor/EditorMainMenu.h>
#include <UWUEngine/Editor/EditorWindow.h>
#include <UWUEngine/Editor/EditorWindowManager.h>
#include <UWUEngine/Editor/EditorHelper.h>
#include <UWUEngine/Serialization.h>
#include <UWUEngine/FrameRateController.h>

#include <imgui.h>

namespace
{
  enum class FileMenuActions
  {
    DEFAULT,
    NEW,
    OPEN,
    SAVE,
    SAVE_AS,

    COUNT
  };

  void PopUpSaveAs()
  {
    if (ImGui::BeginPopupModal("Save As"))
    {
      static std::string levelName = "DefaultLevelName";
      Editors::InputText("Level name", &levelName);
      if (ImGui::Button("Save"))
      {
        SerializeLevel(levelName.c_str());
        ImGui::CloseCurrentPopup();
      }
      ImGui::EndPopup();
    }
  }
}

void Editors::DockSpace()
{
  static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

  // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
  // because it would be confusing to have two docking targets within each others.
  ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
  ImGuiViewport* viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(viewport->Pos);
  ImGui::SetNextWindowSize(viewport->Size);
  ImGui::SetNextWindowViewport(viewport->ID);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
  window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

  // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
  dockspace_flags |= ImGuiDockNodeFlags_PassthruCentralNode;
  if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
    window_flags |= ImGuiWindowFlags_NoBackground;

  // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
  // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
  // all active windows docked into it will lose their parent and become undocked.
  // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
  // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
  ImGui::Begin("DockSpace Demo", nullptr, window_flags);
  ImGui::PopStyleVar();
  ImGui::PopStyleVar(2);

  // DockSpace
  ImGuiIO& io = ImGui::GetIO();
  ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
  ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

  ImGui::End();
}

void Editors::MainMenu()
{
  static FileMenuActions fileMenuAction = FileMenuActions::DEFAULT;
  //Pop Ups
  PopUpSaveAs();

  if (ImGui::BeginMainMenuBar())
  {
    if (ImGui::BeginMenu("File"))
    {
      if (ImGui::MenuItem("Open"))
      {
        fileMenuAction = FileMenuActions::OPEN;
      }
      if (ImGui::MenuItem("Save"))
      {
        fileMenuAction = FileMenuActions::SAVE;
      }
      if (ImGui::MenuItem("Save As"))
      {
        fileMenuAction = FileMenuActions::SAVE_AS;
      }
      ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("View"))
    {
      for (auto window : WindowManager::GetWindows())
      {
        const std::string & windowName = window.first;
        const auto & windowContent = window.second;
        if (ImGui::MenuItem(windowName.c_str(), nullptr, windowContent->IsActive()))
        {
          windowContent->ToggleActive();
        }
      }

      ImGui::EndMenu();
    }

    if (ImGui::Button("Pause"))
    {
      static bool isPaused = true;
      isPaused = !isPaused;
      FrameRateController::SetPaused(isPaused);
    }
    ImGui::EndMainMenuBar();
  }

  switch (fileMenuAction)
  {
  case FileMenuActions::NEW: break;
  case FileMenuActions::OPEN: break;
  case FileMenuActions::SAVE:
    SerializeLevel("BrayanSBOX");
    break;
  case FileMenuActions::SAVE_AS:
    ImGui::OpenPopup("Save As");
    break;
  default: ;
  }
  fileMenuAction = FileMenuActions::DEFAULT;
}
