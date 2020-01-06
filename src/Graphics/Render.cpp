/******************************************************************************/
/*!
\par        Project Umbra
\file       Render.cpp
\author     Chau Nguyen
\date       2019/09/13
\brief      Rendering

Copyright � 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#include <UWUEngine/Entity/EntityManager.h>
#include <UWUEngine/Graphics/Render.h>
#include <array>
#include <GL/glew.h>
#include <UWUEngine/Graphics/Shader/glslshader.h>
#include <UWUEngine/Engine.h>
#include "imgui.h"
#include <UWUEngine/Component/SpineSkeletonComponentManager.h>
#include <UWUEngine/Graphics/Shader/ShaderModule.h>
#include <UWUEngine/Component/TextureComponentManager.h>
#include <UWUEngine/Debugs/DebugManager.h>
#include <UWUEngine/Editor.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <UWUEngine/UI/UIManager.h>

namespace wc = WindowConstants;

static GLuint size;
template<>
int RegisterSystemHelper<Render>::RegisterSystemHelper_ID = SystemUpdater::AddSystem<Render>(SystemInitOrder::Render, SystemUpdateOrder::Render);

namespace
{
	void DrawMesh(std::tuple<GLenum, GLuint, GLuint>& mesh);
}

Render::Render()
{
#ifdef _RELEASE
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
#endif
#ifdef _DEBUG
  glClearColor(.2f, .2f, .2f, 1.f);
#endif
	glViewport(0, 0, wc::WINDOW_WIDTH, wc::WINDOW_HEIGHT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.05);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);


	//glEnable(GL_POINT_SMOOTH);
	//OPENGL_ERR;
	//glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	//OPENGL_ERR;
}

void Render::Update()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    
    std::vector<EntityID> ids = EntityManager::GetIDs();
    // TODO: add a function to get size of ids
    size = static_cast<GLuint>(ids.size());
    //TODO: stop dreamming
    const GLSLShader& shader = ShaderModule::GetEntityShader();

    for (auto id : ids)
    {
      if (BehaviorComponentManager::IsActive(id))
      {
        BehaviorComponentManager::GetBaseBehavior(id)->Render();
      }
	    if (SpineSkeletonComponentManager::IsActive(id))
	    {
			SpineSkeletonComponentManager::Render(id);
	    }
    }
    
    VaoKey vao_key = Instances::GetEntityVAOKey();
    GLuint vao = Instances::GetVAOid(vao_key);
    Instances::UpdateInstances(vao_key);
    
    glBindVertexArray(vao); // bind vao 1
    shader.Use();

    // bind to proper texture unit 0
    glBindTextureUnit(0, TextureAtlaser::GetTextureID());

    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, NULL, static_cast<GLsizei>(EntityVectorManager::GetVectorSize()));
    shader.UnUse();
    glBindVertexArray(0);
	

    DebugManager::Render();
    UIManager::Render();


    if (Editor::IsActive())
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}

void Render::DrawObject(EntityID ID)
{
	const GLuint& textureID = TextureComponentManager::GetTextureID(ID);
	// activate texture unit 0

	glActiveTexture(GL_TEXTURE0);
	// binding texture
	glBindTexture(GL_TEXTURE_2D, textureID);

    // sending data to Transformation uniform buffer
    //Engine::shaderManager.ShootDataToUniformBuffer("Transformation", ID);
    
    // sending data to UVCoordClr uniform buffer
    //Engine::shaderManager.ShootDataToUniformBuffer("UVCoordClr", ID);

	// sending data to UVCoordClr uniform buffer
	//ShaderModule::ShootDataToUniformBuffer("UVCoordClr", ID);

	/*const GLSLShader& shader = ShaderModule::GetEntityShader();
	auto mesh = MeshComponentManager::GetMesh(ID);
	glBindVertexArray(std::get<1>(mesh));
	shader.Use();
	//glDrawElementsInstanced(GL_TRIANGLES, std::get<2>(mesh), GL_UNSIGNED_SHORT, NULL, size);
	DrawMesh(mesh);
	shader.UnUse();
	glBindVertexArray(0);*/
}

namespace {
	void DrawMesh(std::tuple<GLenum, GLuint, GLuint>& mesh)
	{
		switch (std::get<0>(mesh))
		{
		case GL_TRIANGLES:
			glDrawElements(GL_TRIANGLES, std::get<2>(mesh), GL_UNSIGNED_SHORT, NULL);
			break;
		case GL_TRIANGLE_STRIP:
			glDrawElements(GL_TRIANGLE_STRIP, std::get<2>(mesh), GL_UNSIGNED_SHORT, NULL);
			break;
		case GL_TRIANGLE_FAN:
			glDrawElements(GL_TRIANGLE_FAN, std::get<2>(mesh), GL_UNSIGNED_SHORT, NULL);
			break;
		case GL_LINES:
			glLineWidth(1.0f);
			glVertexAttrib3f(1, 1.0f, 0.0f, 0.0f);
			glDrawArrays(GL_LINES, 0, std::get<2>(mesh));
			break;
		case GL_LINE_LOOP:
			glLineWidth(1.0f); // Lines are m pixels wide
			glVertexAttrib3f(1, 1.0f, 0.0f, 0.0f);
			glDrawArrays(GL_LINE_LOOP, 0, std::get<2>(mesh));
			break;
		case GL_POINTS:
			glPointSize(20.0f);
			glVertexAttrib3f(1, 1.0f, 0.0f, 0.0f);
			glDrawArrays(GL_POINTS, 0, std::get<2>(mesh));
			break;
		};
	}
}
