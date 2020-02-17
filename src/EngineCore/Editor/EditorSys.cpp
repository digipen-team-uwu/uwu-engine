#include <UWUEngine/Systems/EditorSys.h>
#include <UWUEngine/Systems/WindowSys.h>
#include <UWUEngine/Systems/InputSys.h>
#include <UWUEngine/Editors/WindowManager.h>
#include <UWUEngine/EngineSettings.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

using namespace UWUEngine;

EditorSys::EditorSys(ISpace* p):
  System(p), isActive(false), windowManager(p)
{
  // Establishes ImGui context for the editor window
  ImGui::CreateContext();
  ImGui_ImplGlfw_InitForOpenGL(Get<WindowSys>().getWindowHandle(), true);
  ImGui_ImplOpenGL3_Init("#version 450");

  //Enable ImGui features/flags
  ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
}

EditorSys::~EditorSys()
{
  // Destroys ImGui Window Context
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

void EditorSys::Update()
{
  ToggleActivate();
  if (!IsActive())
  {
    return;
  }

  // Start the dear imgui frame
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  MainMenu();
  DockSpace();
  windowManager.Update();
}

bool EditorSys::IsActive() const
{
  return isActive;
}

void EditorSys::ToggleActivate()
{
  if (EngineSettings::Editor)
  {
    if (Get<InputSys>().KeyPressed(GLFW_KEY_GRAVE_ACCENT))
    {
      isActive = !isActive;
    }
  }
}
