/******************************************************************************/
/*!
\par        Project Umbra
\file       ShaderModule.cpp
\author     Chau Nguyen
\date       2019/09/13
\brief      Managing GLSL Shaders

Copyright � 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#include <UWUEngine/Graphics/Shader/ShaderModule.h>
#include <UWUEngine/Component/TransformComponentManager.h>
#include <UWUEngine/Component/TextureComponentManager.h>
#include <UWUEngine/Graphics/Lighting/Lighting.h>
#include <fstream>
#include <UWUEngine/Debugs/TraceLogger.h>

namespace goc = GameObjectConstants;
GLSLShader ShaderModule::entityShader;
GLSLShader ShaderModule::hudShader;

GLSLShader ShaderModule::CreateShader(const char* vertex_shader_filePath,
    const char* fragment_shader_filePath)
{

    std::vector<std::pair<GLenum, std::string>> shdr_files;
    GLSLShader shdr_pgm{};
    shdr_files.emplace_back(std::make_pair(
        GL_VERTEX_SHADER,
        vertex_shader_filePath));

    shdr_files.emplace_back(std::make_pair(GL_FRAGMENT_SHADER,
        fragment_shader_filePath));

    shdr_pgm.CompileLinkValidate(shdr_files);

    if (GL_FALSE == shdr_pgm.IsLinked()) {
      TraceLogger::Log(TraceLogger::FAILURE) << "Unable to compile/link/validate shader programs" <<
            std::endl;
      TraceLogger::Log(TraceLogger::FAILURE) << shdr_pgm.GetLog() << std::endl;
        std::exit(EXIT_FAILURE);
    }

    return shdr_pgm;
}

GLSLShader ShaderModule::GetEntityShader()
{
  static bool shaderMade = false;
  if (!shaderMade)
  {
    entityShader = CreateShader("./data/shaders/pass-thru-pos2d-clr.vert", "./data/shaders/basic-color.frag");
    shaderMade = true;
  }
  return entityShader;
}

GLSLShader ShaderModule::GetHudShader()
{
    static bool made = false;
    if (!made)
    {
        hudShader = CreateShader("./data/shaders/HUD.vert", "./data/shaders/HUD.frag");
        made = true;
    }
    return hudShader;
}
