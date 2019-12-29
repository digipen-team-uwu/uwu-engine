/******************************************************************************/
/*!
\par        Project Umbra
\file       EditorWindow.cpp
\author     Yi Qian
\date       2019/12/28
\brief      Editor window

Copyright © 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#include <UWUEngine/Editor/EditorWindow.h>
#include <imgui.h>

void EditorWindow::Render()
{
  if (!isActive)
  {
    return;
  }
  if (ImGui::Begin(name.c_str()))
  {
    this->Setup();
    this->Update();
    ImGui::End();
  }
}

void EditorWindow::ToggleActive()
{
  isActive = !isActive;
}

bool EditorWindow::IsActive()
{
  return isActive;
}

bool EditorWindow::IsWindowNamed(std::string& name) const
{
  return name == this->name;
}

const std::string& EditorWindow::GetName() const
{
  return name;
}
