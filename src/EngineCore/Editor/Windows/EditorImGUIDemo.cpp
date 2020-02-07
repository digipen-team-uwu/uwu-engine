#include <UWUEngine/Editor/Windows/EditorImGUIDemo.h>
#include <imgui.h>

Editors::Demo::Demo():
Window("Demo", false, true)
{
}

Editors::Demo::~Demo()
{
}

void Editors::Demo::Setup()
{
}

void Editors::Demo::Update()
{
  ImGui::ShowDemoWindow(SetActive());
}
