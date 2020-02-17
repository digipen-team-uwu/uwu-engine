
#include <UWUEngine/Editors/Windows/Demo.h>
#include <UWUEngine/Systems/LogSys.h>

#include <imgui.h>

using namespace UWUEngine;
using namespace Editors;

Demo::Demo(ISpace* systemSpace) :
  Window(systemSpace, "Demo", false, true)
{
  GetSystem<LogSys>().Log(LogSys::TRACE) << "Demo window initialized" << std::endl;
}

Demo::~Demo()
= default;

void Demo::Setup()
{
}

void Demo::Update()
{
  ImGui::ShowDemoWindow(SetActive());
}
