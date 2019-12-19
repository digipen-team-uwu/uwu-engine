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
#include <UWUEngine/Entity/EntityManager.h>
#include <UWUEngine/Component/BaseComponent.h>
#include <map>
#include <tuple>

class ShaderModule
{
public:
  ShaderModule() = default;
  ~ShaderModule() = default;

    static GLSLShader CreateShader(const char* vertex_shader_filePath,
        const char* fragment_shader_filePath);

    static GLSLShader GetEntityShader();
    static GLSLShader GetHudShader();

private:
    static GLSLShader entityShader;
    static GLSLShader hudShader;
};
