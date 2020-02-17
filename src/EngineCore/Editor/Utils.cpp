/******************************************************************************/
/*!
\par        Project Umbra
\file       Utils.cpp
\author     Yi Qian
\date       2019/12/28
\brief      Editor Helper widgets

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#include <UWUEngine/Systems/EditorSys.h>
#include <UWUEngine/Systems/EventSys.h>
#include <UWUEngine/Systems/SceneSys.h>
#include <UWUEngine/Systems/FrameLimiterSys.h>

#include <UWUEngine/Editors/Window.h>
#include <UWUEngine/Editors/WindowManager.h>
#include <UWUEngine/Editors/Utils.h>

#include <imgui.h>

using namespace UWUEngine;
using namespace Editors;

#pragma region Utils
// Helper to display a little (?) mark which shows a tooltip when hovered.
// In your own code you may want to display an actual icon if you are using a merged icon fonts (see docs/FONTS.txt)
void Editors::HelpMarker(const char* desc)
{
  ImGui::TextDisabled("(?)");
  if (ImGui::IsItemHovered())
  {
    ImGui::BeginTooltip();
    ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
    ImGui::TextUnformatted(desc);
    ImGui::PopTextWrapPos();
    ImGui::EndTooltip();
  }
}

struct InputTextCallback_UserData
{
  std::string* Str;
  ImGuiInputTextCallback  ChainCallback;
  void* ChainCallbackUserData;
};

int InputTextCallback(ImGuiInputTextCallbackData* data)
{
  InputTextCallback_UserData* user_data = (InputTextCallback_UserData*)data->UserData;
  if (data->EventFlag == ImGuiInputTextFlags_CallbackResize)
  {
    // Resize string callback
    // If for some reason we refuse the new length (BufTextLen) and/or capacity (BufSize) we need to set them back to what we want.
    std::string* str = user_data->Str;
    IM_ASSERT(data->Buf == str->c_str());
    str->resize(data->BufTextLen);
    data->Buf = (char*)str->c_str();
  }
  else if (user_data->ChainCallback)
  {
    // Forward to user callback, if any
    data->UserData = user_data->ChainCallbackUserData;
    return user_data->ChainCallback(data);
  }
  return 0;
}

bool Editors::InputText(const char* label, std::string* str, ImGuiInputTextFlags flags, ImGuiInputTextCallback callback, void* user_data)
{
  IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
  flags |= ImGuiInputTextFlags_CallbackResize;

  InputTextCallback_UserData cb_user_data;
  cb_user_data.Str = str;
  cb_user_data.ChainCallback = callback;
  cb_user_data.ChainCallbackUserData = user_data;
  return ImGui::InputText(label, (char*)str->c_str(), str->capacity() + 1, flags, InputTextCallback, &cb_user_data);
}

bool Editors::InputTextMultiline(const char* label, std::string* str, const ImVec2& size, ImGuiInputTextFlags flags, ImGuiInputTextCallback callback, void* user_data)
{
  IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
  flags |= ImGuiInputTextFlags_CallbackResize;

  InputTextCallback_UserData cb_user_data;
  cb_user_data.Str = str;
  cb_user_data.ChainCallback = callback;
  cb_user_data.ChainCallbackUserData = user_data;
  return ImGui::InputTextMultiline(label, (char*)str->c_str(), str->capacity() + 1, size, flags, InputTextCallback, &cb_user_data);
}

bool Editors::InputTextWithHint(const char* label, const char* hint, std::string* str, ImGuiInputTextFlags flags, ImGuiInputTextCallback callback, void* user_data)
{
  IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
  flags |= ImGuiInputTextFlags_CallbackResize;

  InputTextCallback_UserData cb_user_data;
  cb_user_data.Str = str;
  cb_user_data.ChainCallback = callback;
  cb_user_data.ChainCallbackUserData = user_data;
  return ImGui::InputTextWithHint(label, hint, (char*)str->c_str(), str->capacity() + 1, flags, InputTextCallback, &cb_user_data);
}

#pragma endregion 

enum class FileMenuActions
{
  DEFAULT,
  NEW,
  OPEN,
  SAVE,
  SAVE_AS,

  COUNT
};

void EditorSys::PopUpSaveAs()
{
  if (ImGui::BeginPopupModal("Save As"))
  {
    static std::string levelName = "DefaultLevelName";
    InputText("Level name", &levelName);
    if (ImGui::Button("Save"))
    {
      //TODO:Serialization
      //SerializeLevel(levelName.c_str());
      ImGui::CloseCurrentPopup();
    }
    ImGui::EndPopup();
  }
}

void EditorSys::DockSpace() const
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
  const ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
  ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

  ImGui::End();
}

void EditorSys::MainMenu()
{
  static FileMenuActions fileMenuAction = FileMenuActions::DEFAULT;
  //Pop Ups
  PopUpSaveAs();

  if (ImGui::BeginMainMenuBar())
  {
    if (ImGui::BeginMenu("File"))
    {
      if (ImGui::MenuItem("New"))
      {
        Get<EventSys>().Push(Event<EventType::SetNextScene>("Empty"));
      }
      if (ImGui::BeginMenu("Open"))
      {
        for (auto i = Get<SceneSys>().Begin(); i != Get<SceneSys>().End(); ++i)
        {
          if (ImGui::MenuItem(i->first.c_str()))
          {
            Get<EventSys>().Push(Event<EventType::SetNextScene>(i->second.GetName()));
          }
        }
        ImGui::EndMenu();
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
      for (auto window : windowManager.GetWindows())
      {
        const std::string& windowName = window.first;
        const auto& windowContent = window.second;
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
      Get<FrameLimiterSys>().SetPaused(isPaused);
    }
    ImGui::EndMainMenuBar();
  }

  switch (fileMenuAction)
  {
  case FileMenuActions::NEW: break;
  case FileMenuActions::OPEN: break;
  case FileMenuActions::SAVE:

    //SerializeLevel("BrayanSBOX");
    break;
  case FileMenuActions::SAVE_AS:
    ImGui::OpenPopup("Save As");
    break;
  default:;
  }
  fileMenuAction = FileMenuActions::DEFAULT;
}
