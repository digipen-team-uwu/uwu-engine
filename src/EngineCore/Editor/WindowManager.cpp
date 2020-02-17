/******************************************************************************/
/*!
\par        Project Umbra
\file       WindowManager.cpp
\author     Yi Qian
\date       2019/12/28
\brief      Editor window

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#include <UWUEngine/Editors/Window.h>
#include <UWUEngine/Editors/WindowManager.h>

#include <UWUEngine/Editors/Windows/EntityViewer.h>
//#include <UWUEngine/Editor/Windows/EditorComponentViewer.h>
#include <UWUEngine/Editors/Windows/Demo.h>

using namespace UWUEngine;
using namespace Editors;

#define REGISTER_WINDOW(name) \
  std::shared_ptr<Window> name = std::make_shared<Editors::name>(systemSpace); \
  windows.insert({(name)->GetName(), name}); \

WindowManager::WindowManager(ISpace* systemSpace) :
systemSpace(systemSpace)
{
  //Register all windows
  REGISTER_WINDOW(EntityViewer)
  //REGISTER_WINDOW(ComponentViewer)
  REGISTER_WINDOW(Demo)
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

std::shared_ptr<const Window> WindowManager::GetWindow(const std::string& name)
{
  return windows.find(name)->second;
}

std::unordered_map<std::string, std::shared_ptr<Window>> & WindowManager::GetWindows()
{
  return windows;
}
