/******************************************************************************/
/*!
\par        Project Umbra
\file       Editor.cpp
\author     Michael Rollosson Halbhuber
\date       2019/10/16
\brief      A class that allows for the editing of Game Objects and
            levels from within the engine.

Copyright © 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#include <UWUEngine/Editor.h>
#include <UWUEngine/WindowManager.h>
#include <UWUEngine/Input/InputManager.h>
//This include can be removed in the future
#include <UWUEngine/Editor/EditorWindowManager.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <UWUEngine/Editor/EditorMainMenu.h>



bool Editor::isActive = false;

Editor::Editor()
{
  // Establishes ImGui context for the editor window
  ImGui::CreateContext();
  ImGui_ImplGlfw_InitForOpenGL(WindowManager::getWindowHandle(), true);
  ImGui_ImplOpenGL3_Init("#version 450");

  //Enable ImGui features/flags
  ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;

  //Start up the editor window manager
  Editors::WindowManager::StartUp();
}

Editor::~Editor()
{
  // Destroys ImGui Window Context
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

void Editor::Update()
{
  ToggleActivate();
  if (!isActive)
  {
    return;
  }

  // Start the dear imgui frame
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  Editors::MainMenu();
  Editors::DockSpace();
  Editors::WindowManager::Update();

  // Show demo window
  ImGui::ShowDemoWindow();
}

bool Editor::IsActive()
{
  return isActive;
}

void Editor::ToggleActivate()
{
  if (InputManager::KeyPressed(GLFW_KEY_GRAVE_ACCENT))
  {
    isActive = !isActive;
  }
}
