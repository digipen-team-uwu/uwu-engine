/******************************************************************************/
  /*!
  \par        Project Umbra
  \file       UISys.cpp
  \author     Hadi Alhussieni
  \date       2019/12/05
  \brief      Implementation for UI rendering

  Copyright � 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#include <UWUEngine/UI/UISys.h>
#include <UWUEngine/constants.h>
#include <UWUEngine/Graphics/Shader/ShaderModule.h>
#include <UWUEngine/Graphics/Shader/UniformBufferSystem.h>

namespace UWUEngine
{
namespace ui = UIConstants;

namespace wc = WindowConstants;
namespace cc = CameraConstants;

UISys::UISys(ISpace* p) : System(p), UIKey(0), bufferSize(0)
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

void UISys::PushElement(float rotate, const glm::vec4& location, const glm::vec3& size, const glm::vec4& colour, const glm::vec2& uv, const glm::uvec2& dimensions, const glm::vec2& atlasuv, const glm::vec2& atlasscale, unsigned atlaslayer)
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

void UISys::Update()
{}

void UISys::Render()
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

const glm::mat4& UISys::GetProjection()
{
  return projection;
}

const glm::mat4& UISys::GetView()
{
  return view;
}

} // namespace UWUEngine
