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
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

template<>
int RegisterSystemHelper<Editor>::RegisterSystemHelper_ID = SystemUpdater::AddSystem<Editor>(SystemInitOrder::Editor, SystemUpdateOrder::Editor);

Editor::Editor()
{
  // Establishes ImGui context for the editor window
  ImGui::CreateContext();
  ImGui_ImplGlfw_InitForOpenGL(WindowManager::getWindowHandle(), true);
  ImGui_ImplOpenGL3_Init("#version 450");
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
  // Start the dear imgui frame
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}

//The following are place holder functions that should never be used
void Editor::Start()
{
}

void Editor::Stop()
{
}

bool Editor::IsActive()
{
  return true;
}
