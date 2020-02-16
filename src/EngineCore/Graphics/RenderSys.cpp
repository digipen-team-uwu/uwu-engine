#include <UWUEngine/Systems/RenderSys.h>
#include <UWUEngine/Systems/LogSys.h>
#include <UWUEngine/Systems/CompSpaceSys.h>
#include <UWUEngine/Systems/EditorSys.h>

#include <UWUEngine/Component/SpineSkeletonComp.h>

#include <UWUEngine/constants.h>
#include <UWUEngine/EngineSettings.h>

#include <GL/glew.h>
#include <imgui_impl_opengl3.h>

using namespace UWUEngine;
namespace wc = WindowConstants;

RenderSys::RenderSys(ISpace* p):
System(p)
{
  //OpenGL Setups
#ifdef _RELEASE
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
#endif
#ifdef _DEBUG
	glClearColor(.3f, .3f, .3f, 1.f);
#endif
	glViewport(0, 0, wc::WINDOW_WIDTH, wc::WINDOW_HEIGHT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_ALPHA_TEST);
	//glAlphaFunc(GL_GREATER, 0.05);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	//glEnable(GL_POINT_SMOOTH);
//OPENGL_ERR;
//glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
//OPENGL_ERR;
	Get<LogSys>().Log(Get<LogSys>().WARNING) << "APU IS HERE:\n" << apu << std::endl;
}

RenderSys::~RenderSys()
= default;

void RenderSys::Update()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Iterate through spaces
	  //Iterate through entities
	  //Instanced/Behavior/Spine draw

	auto& compSys = Get<CompSpaceSys>();

	RenderSpine(compSys.space_gameplay.Get<SpineSkeletonComp>());

  if (EngineSettings::Editor)
  {
		ImGui_ImplOpenGL3_NewFrame();
    if (Get<EditorSys>().IsActive())
    {
      ImGui::Render();
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
  }
}

void RenderSys::RenderSpine(SpineSkeletonComp& skelComp)
{
	for (auto i = skelComp.Begin(); i != skelComp.End(); ++i)
	{
	  i->second.Draw();
	}
}