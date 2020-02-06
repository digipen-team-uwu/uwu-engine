#include <UWUEngine/Graphics/Debugs/Picker.h>
#include <UWUEngine/Input/InputManager.h>
#include <UWUEngine/Graphics/Camera.h>
#include <UWUEngine/constants.h>
#include <UWUEngine/WindowManager.h>
#include <UWUEngine/Component/TransformComponentManager.h>
#include "UWUEngine/Editor/Windows/EditorEntityViewer.h"
#include "UWUEngine/Debugs/TraceLogger.h"
#include "UWUEngine/Component/TextureComponentManager.h"
#include <glm/gtx/intersect.hpp>

glm::mat3 Picker::GLFW_to_vp;
glm::mat3 Picker::ndc_to_vp;
glm::mat3 Picker::ndc_to_vf;
glm::vec3 Picker::mouse_world;
EntityID Picker::saved_ID;
float Picker::saved_d;
std::unordered_map<EntityID, float> Picker::ID_and_distance;
bool Picker::switch_;
Picker::state Picker::state_;

Picker::Picker()
{
  switch_ = false;
  state_ = state::RELEASE;
  saved_d = std::numeric_limits<float>::max();
  saved_ID = static_cast<unsigned>(-1);
}

void Picker::Update()
{
  glm::vec2 mousePos = InputManager::GetMousePos();
  CalculateMouseWorld(mousePos);

  if (InputManager::MousePressed(InputConstants::Mouse::LEFT_CLICK))
  {
    TraceLogger::Log(TraceLogger::DEBUG) << "Mouse GLFW: x: " << mousePos.x << " y: " <<
      mousePos.y << std::endl;
    
    TraceLogger::Log(TraceLogger::DEBUG) << "Mouse World x: " << mouse_world.x << " y: " <<
      mouse_world.y << " z: " << mouse_world.z << std::endl;
  
    Pick();
    TraceLogger::Log(TraceLogger::DEBUG) << "chosen ID: " << saved_ID << std::endl;

    if (saved_ID != goc::INVALID_ID)
    {
      switch_ = !switch_;
      state_ = switch_ ? state::PICKED : state::RELEASE;
      Editors::EntityViewer::SetSelectedEntity(saved_ID);
      TextureComponentManager::SetColor(saved_ID, { 1.0f,0.0f,0.0f,1.0f });
      Reset();
    }
    
    auto cameraPos = Camera::GetCameraPosition();
    TraceLogger::Log(TraceLogger::DEBUG) << "camera pos: x: " << cameraPos.x <<
      " y: " << cameraPos.y << " z: " << cameraPos.z << std::endl << std::endl;
  }

}

void Picker::CalculateMouseWorld(glm::vec2 Pos)
{
  glm::vec3 mousePos = glm::vec3(Pos, 1.0f);
  float width = WindowManager::getWindowWidth();
  float height = WindowManager::getWindowHeight();

#pragma region convert glfw to viewport
  GLFW_to_vp = glm::mat3(1.0f);
  GLFW_to_vp[0].x = 1.0f;
  GLFW_to_vp[1].y = -1.0f;
  GLFW_to_vp[2].x = 0.0f;
  GLFW_to_vp[2].y = height;
  GLFW_to_vp[2].z = 1.0f;

  glm::vec3 mouse_vp = GLFW_to_vp * mousePos;
#pragma endregion

#pragma region convert viewport to ndc
  ndc_to_vp = glm::mat3(1.0f);
  ndc_to_vp[0].x = width / 2.0f;
  ndc_to_vp[1].y = height / 2.0f;
  ndc_to_vp[2].x = width / 2.0f + 0.0f;
  ndc_to_vp[2].y = height / 2.0f + 0.0f;
  ndc_to_vp[2].z = 1.0f;

  glm::vec3 mouse_ndc = glm::inverse(ndc_to_vp) * mouse_vp;
#pragma endregion

#pragma region convert ndc to view finder
  float fov = Camera::getFOV();
  float nearDist = Camera::getNearDistance();
  float height_vf = 2.f * nearDist * tanf(glm::radians(fov) / 2.0f);
  float aspectRatio = Camera::getAspectRatio();
  float width_vf = aspectRatio * height_vf;

  ndc_to_vf = glm::mat3(1.0f);
  // symmetric perspective
  ndc_to_vf[0].x = width_vf / 2.0f;
  ndc_to_vf[1].y = height_vf / 2.0f;
  ndc_to_vf[2].x = 0.0f;
  ndc_to_vf[2].y = 0.0f;
  ndc_to_vf[2].z = 1.0f;

  glm::vec3 mouse_vf = ndc_to_vf * mouse_ndc;
#pragma endregion 

#pragma region convert view finder to view frame
  glm::vec4 mouse_v = { mouse_vf.x, mouse_vf.y, -1 * nearDist, 1.f };
#pragma endregion 

#pragma region convert view frame to world
  glm::mat4 world_to_view = Camera::GetViewMatrix();
  glm::mat4 view_to_world = glm::inverse(world_to_view);
  glm::vec4 temp = view_to_world * mouse_v;
  mouse_world = glm::vec3(temp);
#pragma endregion 
}

void Picker::Reset()
{
  saved_d = std::numeric_limits<float>::max();
  saved_ID = goc::INVALID_ID;
  ID_and_distance.clear();
}

void Picker::Pick()
{
  if (Editors::EntityViewer::GetSelectedEntity() != goc::INVALID_ID)
  {
    TextureComponentManager::SetColor(Editors::EntityViewer::GetSelectedEntity(), { 1.0f,1.0f,1.0f,1.0f });
  }
  
  // get a list of current active objects
  auto ids = EntityManager::GetIDs();
  auto cameraPos = Camera::GetCameraPosition();
  for (auto it = ids.begin(); it != ids.end(); ++it)
  {
    // ray form: r(t) = cameraPos + t * (P_world - cameraPos) = cameraPos + t*d
    // get object current position in world coord
    glm::vec3 objectPos = glm::vec3(TransformComponentManager::GetTranslation(*it));

    if (objectPos.z > 0)
    {
      continue;
    }

    // scale factors of object
    glm::vec3 scale = TransformComponentManager::GetScale(*it);

    glm::vec3 bottom_left = { objectPos.x - scale.x / 2, objectPos.y - scale.y / 2 , objectPos.z};
    glm::vec3 top_left = { objectPos.x - scale.x / 2, objectPos.y + scale.y / 2, objectPos.z };
    glm::vec3 bottom_right = { objectPos.x + scale.x / 2, objectPos.y - scale.y / 2, objectPos.z };
    glm::vec3 top_right = { objectPos.x + scale.x / 2, objectPos.y + scale.y / 2, objectPos.z };

    float intersection_dist;

    glm::vec2 baryPosition;

    if (glm::intersectRayTriangle(cameraPos, glm::normalize(mouse_world - cameraPos), top_left, bottom_left, bottom_right,
      baryPosition, intersection_dist) || glm::intersectRayTriangle(cameraPos, glm::normalize(mouse_world - cameraPos), top_right, top_left, bottom_right,
        baryPosition, intersection_dist))
    {
      ID_and_distance[*it] = intersection_dist;
    }
  }
  PickID();
}

void Picker::PickID()
{
  for (auto it = ID_and_distance.begin(); it != ID_and_distance.end(); ++it)
  {
    if (it->second < saved_d)
    {
      saved_d = it->second;
      saved_ID = it->first;
    }
  }
}

glm::vec2 Picker::GetMouseWorld()
{
  return mouse_world;
}


