#include <UWUEngine/Modules/UBOMod.h>
#include <glm/gtc/type_ptr.hpp>
#include <UWUEngine/Systems/CameraSys.h>
#include <UWUEngine/Component/TransformComp.h>
#include <UWUEngine/Component/SpineSkeletonComp.h>
#include <UWUEngine/Systems/CompSpaceSys.h>
#include <UWUEngine/Systems/LightSys.h>

using namespace UWUEngine;
namespace UBC = UniformBufferConstants;

UBOMod::UBOMod(ISpace * space) : System(space)
{
  CreateUniformBuffer(Light,
    5 * sizeof(glm::vec3) + 5 * UBC::MEMORY_LAYOUT_OFFSET, 0);

  CreateUniformBuffer(Camera,
    2 * sizeof(glm::mat4), 1);

  CreateUniformBuffer(HUDMatrices,
    2 * sizeof(glm::mat4), 2);

  CreateUniformBuffer(Spine,
    2 * sizeof(glm::mat4), 3);
}

void UBOMod::CreateUniformBuffer(UBOMod::Type name, unsigned size, unsigned location)
{
  GLuint ubo;
  glCreateBuffers(1, &ubo);
  glBindBuffer(GL_UNIFORM_BUFFER, ubo);
  //glNamedBufferData(ubo, size, nullptr, GL_DYNAMIC_DRAW);
  glNamedBufferStorage(ubo, size, nullptr, GL_DYNAMIC_STORAGE_BIT);
  glBindBuffer(GL_UNIFORM_BUFFER, location);
  glBindBufferRange(GL_UNIFORM_BUFFER, location, ubo, 0, size);
  glBindBuffer(GL_UNIFORM_BUFFER, 0); // done! unbind

  data_[name].first = ubo;
  data_[name].second = location;
}

unsigned UBOMod::GetUniformBufferBindingLocation(UBOMod::Type name)
{
  return data_[name].second;
}

unsigned UBOMod::GetUniformBufferID(UBOMod::Type name)
{
  return data_[name].first;
}

void UBOMod::ShootDataToUniformBuffer(UBOMod::Type name, EntityID ID)
{
  if (name == Camera)
  {
    glBindBuffer(GL_UNIFORM_BUFFER, data_[name].first);
    glBufferSubData(GL_UNIFORM_BUFFER,
      0,
      sizeof(glm::mat4),
      glm::value_ptr(Get<CameraSys>().GetProjectionMatrix()));
    glBufferSubData(GL_UNIFORM_BUFFER,
      sizeof(glm::mat4),
      sizeof(glm::mat4),
      glm::value_ptr(Get<CameraSys>().GetViewMatrix()));
    glBindBuffer(GL_UNIFORM_BUFFER, data_[name].second);
  }
  //else if (name == HUDMatrices)
  //{
  //  glBindBuffer(GL_UNIFORM_BUFFER, data_[name].first);
  //  glBufferSubData(GL_UNIFORM_BUFFER,
  //    0,
  //    sizeof(glm::mat4),
  //    glm::value_ptr(UIManager::GetProjection()));
  //  glBufferSubData(GL_UNIFORM_BUFFER,
  //    sizeof(glm::mat4),
  //    sizeof(glm::mat4),
  //    glm::value_ptr(UIManager::GetView()));
  //  glBindBuffer(GL_UNIFORM_BUFFER, data_[name].second);
  //}
  else if (name == Spine)
  {
    auto& compSys = Get<CompSpaceSys>();
    auto& gamePlaySpace = compSys.space_gameplay;

    glBindBuffer(GL_UNIFORM_BUFFER, data_[name].first);
    glBufferSubData(GL_UNIFORM_BUFFER,
      0,
      sizeof(glm::mat4),
      glm::value_ptr(gamePlaySpace.Get<TransformComp>().GetSpineModelMatrix(ID)));
    glBufferSubData(GL_UNIFORM_BUFFER,
      sizeof(glm::mat4),
      sizeof(glm::mat4),
      glm::value_ptr(gamePlaySpace.Get<SpineSkeletonComp>().GetScaleOffSet(ID)));
    glBindBuffer(GL_UNIFORM_BUFFER, data_[name].second);
  }
  else if (name == Light)
  {
    auto& lightSys = Get<LightSys>();
    auto& lightPos = lightSys.GetLightPosition();
    auto& lightView = lightSys.GetLightViewPosition();
    auto& lightAmbient = lightSys.GetLightAmbient();
    auto& lightDiffuse = lightSys.GetLightDiffuse();
    auto& lightSpecular = lightSys.GetLightSpecular();
  
    glBindBuffer(GL_UNIFORM_BUFFER, data_[name].first);
    // ambient
    glBufferSubData(GL_UNIFORM_BUFFER,
      0,
      sizeof(glm::vec3),
      glm::value_ptr(lightPos));
    glBufferSubData(GL_UNIFORM_BUFFER,
      sizeof(glm::vec3) + UBC::MEMORY_LAYOUT_OFFSET,
      sizeof(glm::vec3),
      glm::value_ptr(lightView));
    glBufferSubData(GL_UNIFORM_BUFFER,
      2 * sizeof(glm::vec3) + 2 * UBC::MEMORY_LAYOUT_OFFSET,
      sizeof(glm::vec3),
      glm::value_ptr(lightAmbient));
    glBufferSubData(GL_UNIFORM_BUFFER,
      3 * sizeof(glm::vec3) + 3 * UBC::MEMORY_LAYOUT_OFFSET,
      sizeof(glm::vec3),
      glm::value_ptr(lightDiffuse));
    glBufferSubData(GL_UNIFORM_BUFFER,
      4 * sizeof(glm::vec3) + 4 * UBC::MEMORY_LAYOUT_OFFSET,
      sizeof(glm::vec3),
      glm::value_ptr(lightSpecular));
    glBindBuffer(GL_UNIFORM_BUFFER, data_[name].second);
  }

}