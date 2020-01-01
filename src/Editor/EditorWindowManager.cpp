/******************************************************************************/
/*!
\par        Project Umbra
\file       EditorWindowManager.cpp
\author     Yi Qian
\date       2019/12/28
\brief      Editor window

Copyright © 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#include <UWUEngine/Editor/EditorWindow.h>
#include <UWUEngine/Editor/EditorWindowManager.h>

#include <UWUEngine/Editor/Windows/EditorEntityViewer.h>
#include <UWUEngine/Editor/Windows/EditorComponentViewer.h>

using namespace Editors;

std::unordered_map<std::string, std::shared_ptr<Window> > WindowManager::windows;

#define REGISTER_WINDOW(name) \
  std::shared_ptr<Window> name = std::make_shared<Editors::name>(); \
  windows.insert({(name)->GetName(), name}); \

void WindowManager::StartUp()
{
  //Register all windows
  REGISTER_WINDOW(EntityViewer)
  REGISTER_WINDOW(ComponentViewer)
}

void WindowManager::Update()
{
  for (auto window : windows)
  {
    window.second->Render();
  }
}

void WindowManager::ToggleWindow(std::string& name)
{
  windows.find(name)->second->ToggleActive();
}

std::shared_ptr<Window> WindowManager::GetWindow(std::string name)
{
  return windows.find(name)->second;
}
