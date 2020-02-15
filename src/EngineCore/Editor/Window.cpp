/******************************************************************************/
/*!
\par        Project Umbra
\file       EditorWindow.cpp
\author     Yi Qian
\date       2019/12/28
\brief      Editor window

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#include <UWUEngine/Editors/Window.h>
#include <imgui.h>

using namespace UWUEngine::Editors;

void Window::Render()
{
  if (!isActive)
  {
    return;
  }
  this->Setup();
  if (ImGui::Begin(name.c_str()))
  {
    this->Update();
  }
  ImGui::End();
}

void Window::ToggleActive()
{
  isActive = !isActive;
}

bool Window::IsActive()
{
  return isActive;
}

bool Window::IsWindowNamed(std::string& name) const
{
  return name == this->name;
}

const std::string& Window::GetName() const
{
  return name;
}
