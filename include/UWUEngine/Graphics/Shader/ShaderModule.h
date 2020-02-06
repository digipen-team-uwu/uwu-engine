/******************************************************************************/
/*!
\par        Project Umbra
\file       SpriteComponentManager.h
\author     Chau Nguyen
\date       2019/09/13
\brief      Managing meshes

Copyright © 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#pragma once
#include <UWUEngine/Graphics/Shader/glslshader.h>
#include <UWUEngine/System.h>

namespace UWUEngine
{

class ShaderModule : System
{
public:
  ShaderModule(ISpace*);
  ~ShaderModule() = default;

  GLSLShader CreateShader(const char* vertex_shader_filePath,
                                 const char* fragment_shader_filePath) const;
  GLSLShader CreateComputeShader(char const* compute_shader_filePath) const;
  GLSLShader GetEntityShader();
  GLSLShader GetHudShader();

private:
  GLSLShader entityShader;
  GLSLShader hudShader;
};

}