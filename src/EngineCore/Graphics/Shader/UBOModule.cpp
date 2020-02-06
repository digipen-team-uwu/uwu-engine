#include <UWUEngine/Graphics/Shader/UBOModule.h>
#include <UWUEngine/Engine.h>
#include <glm/gtc/type_ptr.hpp>
#include <UWUEngine/Graphics/CameraSys.h>
#include <UWUEngine/Graphics/Lighting/Lighting.h>
#include <UWUEngine/UI/HUDSys.h>
#include <UWUEngine/UI/UISys.h>
#include <UWUEngine/Component/TransformComponentManager.h>
#include <UWUEngine/Component/SpineSkeletonComponentManager.h>

namespace UBC = UniformBufferConstants;

namespace UWUEngine
{

UBOModule::UBOModule(ISpace* p) : System(p)
{
  CreateUBO(Light,5 * sizeof(glm::vec3) + 5 * UBC::MEMORY_LAYOUT_OFFSET, 0);

  CreateUBO(Camera, 2 * sizeof(glm::mat4), 1);

  CreateUBO(HUDMatrices, 2 * sizeof(glm::mat4), 2);

  CreateUBO(Spine, 2 * sizeof(glm::mat4), 3);
}

void UBOModule::CreateUBO(Type name, unsigned size, unsigned location)
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

unsigned UBOModule::GetUBOBindingLocation(Type name)
{
  return data_[name].second;
}

unsigned UBOModule::GetUBO_ID(Type name)
{
  return data_[name].first;
}

void UBOModule::ShootDataToUBO(Type name, EntityID ID)
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
  else if (name == HUDMatrices)
  {
    glBindBuffer(GL_UNIFORM_BUFFER, data_[name].first);
    glBufferSubData(GL_UNIFORM_BUFFER,
                    0,
                    sizeof(glm::mat4),
                    glm::value_ptr(Get<UISys>().GetProjection()));
    glBufferSubData(GL_UNIFORM_BUFFER,
                    sizeof(glm::mat4),
                    sizeof(glm::mat4),
                    glm::value_ptr(Get<UISys>().GetView()));
    glBindBuffer(GL_UNIFORM_BUFFER, data_[name].second);
  }
  else if (name == Spine)
  {
    glBindBuffer(GL_UNIFORM_BUFFER, data_[name].first);
    glBufferSubData(GL_UNIFORM_BUFFER,
                    0,
                    sizeof(glm::mat4),
                    glm::value_ptr(TransformComponentManager::GetSpineModelMatrix(ID)));
    glBufferSubData(GL_UNIFORM_BUFFER,
                    sizeof(glm::mat4),
                    sizeof(glm::mat4),
                    glm::value_ptr(SpineSkeletonComp::GetScaleOffSet(ID)));
    glBindBuffer(GL_UNIFORM_BUFFER, data_[name].second);
  }
  else if (name == Light)
  {
    auto& lightPos = Lighting::GetLightPosition();
    auto& lightView = Lighting::GetLightViewPosition();
    auto& lightAmbient = Lighting::GetLightAmbient();
    auto& lightDiffuse = Lighting::GetLightDiffuse();
    auto& lightSpecular = Lighting::GetLightSpecular();

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

}