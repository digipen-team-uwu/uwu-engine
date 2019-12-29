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

std::unordered_map<std::string, std::shared_ptr<EditorWindow> > EditorWindowManager::windows;

#define REGISTER_WINDOW(name) \
std::shared_ptr<EditorWindow> name = std::make_shared<Editor ## name ##>(); \
windows.insert({(name)->GetName(), name}); \

void EditorWindowManager::StartUp()
{
  //Register all windows
  REGISTER_WINDOW(EntityViewer)
}

void EditorWindowManager::Update()
{
  for (auto window : windows)
  {
    window.second->Render();
  }
}

void EditorWindowManager::ToggleWindow(std::string& name)
{
  windows.find(name)->second->ToggleActive();
}

std::shared_ptr<EditorWindow> EditorWindowManager::GetWindow(std::string name)
{
  return windows.find(name)->second;
}
