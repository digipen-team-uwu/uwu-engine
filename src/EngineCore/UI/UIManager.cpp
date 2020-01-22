/******************************************************************************/
  /*!
  \par        Project Umbra
  \file       UIManager.cpp
  \author     Hadi Alhussieni
  \date       2019/12/05
  \brief      Implementation for UI rendering

  Copyright � 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#include <UWUEngine/UI/UIManager.h>
#include <UWUEngine/Engine.h>
#include <UWUEngine/constants.h>
#include <UWUEngine/Graphics/Shader/ShaderModule.h>
#include <UWUEngine/UI/HUDManager.h>
#include <UWUEngine/Graphics/Shader/UniformBufferSystem.h>



VaoKey UIManager::UIKey;
std::tuple<GLenum, GLuint, GLuint> UIManager::uiMesh;
std::vector<float> UIManager::rotation;
std::vector<glm::vec4> UIManager::translation;
std::vector<glm::vec3> UIManager::scale;
std::vector<glm::vec4> UIManager::color;
std::vector<glm::vec2> UIManager::uvs;
std::vector<glm::uvec2> UIManager::dims;
std::vector<glm::vec2> UIManager::atlasUVs;
std::vector<glm::vec2> UIManager::atlasScale;
std::vector<unsigned> UIManager::atlasLayer;
size_t UIManager::bufferSize = 0;

glm::mat4 UIManager::projection;
glm::mat4 UIManager::view;

namespace ui = UIConstants;

namespace wc = WindowConstants;
namespace cc = CameraConstants;

UIManager::UIManager()
{
    projection = glm::mat4(1.f);
    projection[0].x = 2.f / wc::WINDOW_WIDTH;
    projection[1].y = 2.f / wc::WINDOW_HEIGHT;

    glm::mat4 cam = glm::mat4(1.0f);
    cam[0].x = 1.f;
    cam[1].y = 1.f;
    cam[2].z = 1.f;
    cam[3].x = 0.0f;
    cam[3].y = 0.0f;

    view = glm::inverse(cam);
  uiMesh = MeshComponentManager::getSquareMesh();
}

void UIManager::PushElement(float rotate, const glm::vec4 &location, const glm::vec3 &size, const glm::vec4 &colour, const glm::vec2 &uv , const glm::uvec2& dimensions, const glm::vec2 &atlasuv, const glm::vec2 &atlasscale, unsigned atlaslayer)
{
  rotation.push_back(rotate);
  translation.push_back(location);
  scale.push_back(size);
  color.push_back(colour);
  uvs.push_back(uv);
  dims.push_back(dimensions);
  atlasUVs.push_back(atlasuv);
  atlasScale.push_back(atlasscale);
  atlasLayer.push_back(atlaslayer);
  if (rotation.capacity() > bufferSize)
  {
    UIKey = Instances::CreateInstancesHUD(uiMesh, GL_ELEMENT_ARRAY_BUFFER, &rotation, &translation, &scale, &color, &uvs, &dims, &atlasUVs, &atlasScale, &atlasLayer);
    bufferSize = rotation.capacity();
  }
}

void UIManager::Update()
{
}

void UIManager::Render()
{
    Instances::UpdateInstancesHUD(UIKey, &rotation, &translation, &scale, &color, &uvs, &dims, &atlasUVs, &atlasScale, &atlasLayer);
    GLSLShader shader = ShaderModule::GetHudShader();
    shader.Use();
    glBindVertexArray(Instances::GetVAOid(UIKey));

    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, NULL, static_cast<GLsizei>(bufferSize));

    UniformBuffer::ShootDataToUniformBuffer(UniformBuffer::Type::HUDMatrices);

    glBindVertexArray(0);
    shader.UnUse();

    rotation.clear();
    translation.clear();
    scale.clear();
    color.clear();
    std::fill(uvs.begin(), uvs.end(), glm::vec2{ -1, -1 });
    uvs.clear();
    dims.clear();
    atlasUVs.clear();
    atlasScale.clear();
    atlasLayer.clear();
}

const glm::mat4& UIManager::GetProjection()
{
    return projection;
}

const glm::mat4& UIManager::GetView()
{
    return view;
}

/*
void UIManager::ResizeBufferIfNecessary()
{
  translation.size() >= bufferSize;
  {
    if (bufferSize > 0)
    {
      bufferSize *= 2;
    }
    else
    {
      bufferSize = 1;
    }
    rotation.resize(bufferSize, 0);
    translation.resize(bufferSize);
    scale.resize(bufferSize);
    color.resize(bufferSize);
    uvs.resize(bufferSize, { -1, -1 });
    dims.resize(bufferSize, { 1, 1 });
    atlasUVs.resize(bufferSize);
    atlasScale.resize(bufferSize);
    Engine::instances.CreateInstances(uiMesh);
  }
}
*/