#include <UWUEngine/Graphics/Debugs/Picker.h>
#include <UWUEngine/Input/InputManager.h>
#include <UWUEngine/Graphics/Camera.h>
#include <UWUEngine/constants.h>
#include <UWUEngine/WindowManager.h>
#include <UWUEngine/Component/TransformComponentManager.h>
#include "UWUEngine/Editor/Windows/EditorEntityViewer.h"
#include "UWUEngine/Debugs/TraceLogger.h"
#include "UWUEngine/Component/TextureComponentManager.h"

template<>
int RegisterSystemHelper<Picker>::RegisterSystemHelper_ID = SystemUpdater::AddSystem<Picker>(SystemInitOrder::LAST, SystemUpdateOrder::Picker);

glm::mat3 Picker::GLFW_to_vp;
glm::mat3 Picker::ndc_to_vp;
glm::mat3 Picker::ndc_to_vf;
glm::vec3 Picker::mouse_world;
glm::vec3 Picker::ray_world;
EntityID Picker::saved_ID;
float Picker::saved_z;
std::unordered_map<EntityID, float> Picker::ID_and_depth;

Picker::Picker()
{
  saved_z = FLT_MAX;
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
    TraceLogger::Log(TraceLogger::DEBUG) << "Ray World x: " << ray_world.x << " y: " <<
      ray_world.y << " z: " << ray_world.z << std::endl;

    Pick();
    PickID();
    TraceLogger::Log(TraceLogger::DEBUG) << "chosen ID: " << saved_ID << std::endl;

    Editors::EntityViewer::SetSelectedEntity(saved_ID);

    //TextureComponentManager::SetColor(saved_ID, { 1.0f,0.0f,0.0f,1.0f });
    //Reset();
    //auto pos = TransformComponentManager::GetTranslation(saved_ID);
    //TraceLogger::Log(TraceLogger::DEBUG) << "current obj pos: x: " << pos.x <<
    //  " y: " << pos.y << " z: " << pos.z << std::endl;
    //
    //TransformComponentManager::SetTranslation(
    //  { mouse_world.x,
    //    mouse_world.y,
    //    pos.z,1.0f },
    //  saved_ID);
    //
    //pos = TransformComponentManager::GetTranslation(saved_ID);
    //TraceLogger::Log(TraceLogger::DEBUG) << "after obj pos: x: " << pos.x <<
    //  " y: " << pos.y << " z: " << pos.z << std::endl;
    //
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
  
  //float x = (2.0f * mousePos.x) / width - 1.0f;
  //float y = 1.0f - (2.0f * mousePos.y) / height;
  //float z = 1.0f;
  //glm::vec3 ray_nds = { x,y,z };
  //glm::vec4 ray_clip = { ray_nds.x, ray_nds.y, -1.0f, 1.0f };
  //glm::vec4 ray_eye = glm::inverse(Camera::GetProjectionMatrix()) * ray_clip;
  //ray_eye.z = -1.0f;
  //ray_eye.w = 0.0f;
  //glm::vec3 ray_wor = glm::vec3(glm::inverse(Camera::GetViewMatrix()) * ray_eye);
  //ray_wor = glm::normalize(ray_wor);
  //ray_world = ray_wor;

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
  saved_z = FLT_MAX;
  saved_ID = static_cast<unsigned>(-1);
}

bool Picker::IsPointInAABB(AABB aabb, Point p)
{
  return p.x >= aabb.bottom_left.x &&
         p.y >= aabb.bottom_left.y &&
         p.x <= aabb.bottom_left.x + aabb.w &&
         p.y <= aabb.bottom_left.y + aabb.h;
}

void Picker::Pick()
{
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

    AABB rect = { scale.x, scale.y, bottom_left };

    auto cameraPos = Camera::GetCameraPosition();
    glm::vec3 n = { 0.0f,0.0f,1.0f };
    glm::vec3 cam_to_obj = cameraPos - objectPos;


    float distance = glm::abs(glm::dot(cam_to_obj, n)) / n.length();

    // (cameraPos + ray_world*t) . n + d = 0
    float numerator = glm::dot(cameraPos, n) + distance;
    float denominator = glm::dot(ray_world, n);
    float t = -numerator / denominator;

    if (t > 0)
    {
      ID_and_depth[*it] = t;
    }

    //if (IsPointInAABB(rect, mouse_world))
    //{
    //  ID_and_depth[*it] = objectPos.z;
    //}
    
  }
}

void Picker::PickID()
{
  for (auto it = ID_and_depth.begin(); it != ID_and_depth.end(); ++it)
  {
    if (it->second < saved_z)
    {
      saved_z = it->second;
      saved_ID = it->first;
    }
  }
}

glm::vec2 Picker::GetMouseWorld()
{
  return mouse_world;
}


