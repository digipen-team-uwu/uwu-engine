#include <UWUEngine/Graphics/Debugs/Picker.h>
#include <UWUEngine/Input/InputManager.h>
#include <UWUEngine/Graphics/Camera.h>
#include <UWUEngine/constants.h>
#include <UWUEngine/WindowManager.h>
#include <UWUEngine/Component/TransformComponentManager.h>
#include "UWUEngine/Editor/Windows/EditorEntityViewer.h"
#include "UWUEngine/Debugs/TraceLogger.h"

template<>
int RegisterSystemHelper<Picker>::RegisterSystemHelper_ID = SystemUpdater::AddSystem<Picker>(SystemInitOrder::LAST, SystemUpdateOrder::Picker);

glm::vec3 Picker::mouse_world;
EntityID Picker::saved_ID;
float Picker::saved_t;
std::unordered_map<EntityID, float> Picker::ID_to_time_;

Picker::Picker()
{
  saved_t = 1000.f;
  saved_ID = static_cast<unsigned>(-1);
}

void Picker::Update()
{
  
  if (InputManager::MousePressed(InputConstants::Mouse::LEFT_CLICK))
  {
    glm::vec2 mousePos = InputManager::GetMousePos();
    TraceLogger::Log(TraceLogger::DEBUG) << "Mouse GLFW: x: " << mousePos.x << " y: " <<
      mousePos.y << std::endl;

    CalculateMouseWorld(mousePos);
    TraceLogger::Log(TraceLogger::DEBUG) << "Mouse World x: " << mouse_world.x << " y: " <<
      mouse_world.y << " z: " << mouse_world.z << std::endl;

    Pick();
    PickID();
    TraceLogger::Log(TraceLogger::DEBUG) << "chosen ID: " << saved_ID << std::endl;

    Editors::EntityViewer::SetSelectedEntity(saved_ID);

    auto pos = TransformComponentManager::GetTranslation(saved_ID);
    TraceLogger::Log(TraceLogger::DEBUG) << "current obj pos: x: " << pos.x <<
      " y: " << pos.y << " z: " << pos.z << std::endl;

    TransformComponentManager::SetTranslation(
      { mouse_world.x,
        mouse_world.y,
        pos.z,1.0f },
      saved_ID);

    pos = TransformComponentManager::GetTranslation(saved_ID);
    TraceLogger::Log(TraceLogger::DEBUG) << "after obj pos: x: " << pos.x <<
      " y: " << pos.y << " z: " << pos.z << std::endl << std::endl;
  }
}

void Picker::CalculateMouseWorld(glm::vec2 Pos)
{
  glm::vec3 mousePos = glm::vec3(Pos, 1.0f);

#pragma region convert glfw to viewport
  glm::mat3 GLFW_to_vp(1.0f);
  GLFW_to_vp[0].x = 1.0f;
  GLFW_to_vp[1].y = -1.0f;
  GLFW_to_vp[2].x = 0.0f;
  GLFW_to_vp[2].y = WindowManager::getWindowHeight();
  GLFW_to_vp[2].z = 1.0f;
#pragma endregion

#pragma region convert viewport to ndc
  glm::mat3 ndc_to_vp(1.0f);
  ndc_to_vp[0].x = WindowManager::getWindowWidth() / 2.0f;
  ndc_to_vp[1].y = WindowManager::getWindowHeight() / 2.0f;
  ndc_to_vp[2].x = WindowManager::getWindowWidth() / 2.0f + 0.0f;
  ndc_to_vp[2].y = WindowManager::getWindowHeight() / 2.0f + 0.0f;
  ndc_to_vp[2].z = 1.0f;
  glm::mat3 vp_to_ndc = glm::inverse(ndc_to_vp);
#pragma endregion

#pragma region convert ndc to view finder
  float fov = Camera::getFOV();
  float nearDist = Camera::getNearDistance();
  float height_vf = 2.f * nearDist * tanf(glm::radians(fov) / 2.0f);
  float aspectRatio = Camera::getAspectRatio();
  float width_vf = aspectRatio * height_vf;

  glm::mat3 ndc_to_vf(1.0f);
  // asymmetric perspective
  //ndc_to_vf[0].x = width_vf / 2.0f;
  //ndc_to_vf[1].y = height_vf / 2.0f;
  //ndc_to_vf[2].x = 0.0f;
  //ndc_to_vf[2].y = 0.0f;
  //ndc_to_vf[2].z = 1.0f;
  // symmetric perspective
  ndc_to_vf[0].x = 1.0f / tan(fov / 2.0f) / aspectRatio;
  ndc_to_vf[1].y = 1.0f / tan(fov / 2.0f);
#pragma endregion 

#pragma region convert view finder to view frame
  glm::vec3 P_vf = ndc_to_vf * vp_to_ndc * GLFW_to_vp * mousePos;
  glm::vec4 P_view = { P_vf.x, P_vf.y, -1 * nearDist, 1.f };
#pragma endregion 

#pragma region convert view frame to world
  glm::mat4 view_to_world = glm::inverse(Camera::GetViewMatrix());
  mouse_world = glm::vec3(view_to_world * P_view);
#pragma endregion 
}

void Picker::Pick()
{
  glm::vec3 cameraPos = Camera::GetCameraPosition();

  // get a list of current active objects
  auto ids = EntityManager::GetIDs();

  for (auto it = ids.begin(); it != ids.end(); ++it)
  {
    // ray form: r(t) = cameraPos + t * (P_world - cameraPos) = cameraPos + t*d
    // get object current position in world coord
    glm::vec3 objectPos = glm::vec3(TransformComponentManager::GetTranslation(*it));

    // scale factors of object
    glm::vec3 scale = TransformComponentManager::GetScale(*it);

    // calculate normal of the plane
    glm::vec3 bottom_left = { objectPos.x - scale.x / 2.f, objectPos.y - scale.y / 2.f, objectPos.z };
    glm::vec3 top_left = { objectPos.x - scale.x / 2.f, objectPos.y + scale.y / 2.f, objectPos.z };
    glm::vec3 bottom_right = { objectPos.x + scale.x / 2.f, objectPos.y - scale.y / 2.f, objectPos.z };

    glm::vec3 u = top_left - bottom_left;
    glm::vec3 v = bottom_right - bottom_left;
    glm::vec3 n = glm::normalize(glm::cross(v, u));

    // ray direction
    glm::vec3 d = glm::normalize(mouse_world - cameraPos);

    float denom = glm::dot(d, n);
    // plane and ray are not parallel
    if (denom > 1e-6)
    {
      float numerator = glm::dot(glm::normalize(objectPos - cameraPos), n);
      float t = numerator / denom;
      if (t >= 0)
      {
        ID_to_time_[*it] = t;
      }
    }
  }
}

void Picker::PickID()
{
  for (auto it = ID_to_time_.begin(); it != ID_to_time_.end(); ++it)
  {
    if (it->second < saved_t)
    {
      saved_t = it->second;
      saved_ID = it->first;
    }
  }
}

glm::vec3 Picker::GetMouseWorld()
{
  return mouse_world;
}


