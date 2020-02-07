#include <UWUEngine/Graphics/Debugs/Picker.h>
#include <UWUEngine/Input/InputManager.h>
#include <UWUEngine/Graphics/Camera.h>
#include <UWUEngine/constants.h>
#include <UWUEngine/WindowManager.h>
#include <UWUEngine/Component/TransformComponentManager.h>
#include <UWUEngine/Editor/Windows/EditorEntityViewer.h>
#include <UWUEngine/Debugs/TraceLogger.h>
#include <UWUEngine/Component/TextureComponentManager.h>
#include <glm/gtx/intersect.hpp>
#include <UWUEngine/Graphics/Texture/TextureAtlaser.h>
#include <glm/gtx/transform.hpp>


glm::mat3 Picker::GLFW_to_vp;
glm::mat3 Picker::ndc_to_vp;
glm::mat3 Picker::ndc_to_vf;
glm::vec3 Picker::mouse_world;
EntityID Picker::saved_ID;
float Picker::saved_d;
std::map<float, Picker::PickerData> Picker::Data_;
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
      state_ = state::PICKED;
      //switch_ = !switch_;
      //state_ = switch_ ? state::PICKED : state::RELEASE;
      Editors::EntityViewer::SetSelectedEntity(saved_ID);
      TextureComponentManager::SetColor(saved_ID, { 1.0f,0.0f,0.0f,1.0f });
      Reset();
    }
    
    auto cameraPos = Camera::GetCameraPosition();
    TraceLogger::Log(TraceLogger::DEBUG) << "camera pos: x: " << cameraPos.x <<
      " y: " << cameraPos.y << " z: " << cameraPos.z << std::endl << std::endl;
  }
  if (InputManager::MouseReleased(InputConstants::Mouse::LEFT_CLICK))
  {
    state_ = state::RELEASE;
  }
  if (state_ == state::PICKED)
  {
    auto chosen_ID = Editors::EntityViewer::GetSelectedEntity();
    DragObject(chosen_ID);
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

void Picker::DragObject(EntityID chosen_ID)
{
  auto mouse_offset = Camera::getMouseOffset();
  auto chosen_obj_pos = TransformComponentManager::GetTranslation(chosen_ID);
  chosen_obj_pos.x += mouse_offset.x * 5.f;
  chosen_obj_pos.y += mouse_offset.y * 5.f;
  TransformComponentManager::SetTranslation(chosen_obj_pos, chosen_ID);
}

void Picker::Reset()
{
  saved_d = std::numeric_limits<float>::max();
  saved_ID = goc::INVALID_ID;
  Data_.clear();
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

    //if (objectPos.z > 0)
    //{
    //  continue;
    //}

    // scale factors of object
    glm::vec3 scale = TransformComponentManager::GetScale(*it);

    float rotation = TransformComponentManager::GetRotation(*it);

    glm::vec3 bottom_left = { objectPos.x - scale.x / 2, objectPos.y - scale.y / 2 , objectPos.z };
    glm::vec3 top_left = { objectPos.x - scale.x / 2, objectPos.y + scale.y / 2, objectPos.z };
    glm::vec3 bottom_right = { objectPos.x + scale.x / 2, objectPos.y - scale.y / 2, objectPos.z };
    glm::vec3 top_right = { objectPos.x + scale.x / 2, objectPos.y + scale.y / 2, objectPos.z };

    if (rotation != 0.f)
    {
      glm::mat4 translate = glm::mat4(1.0f);
      translate[3] = glm::vec4(objectPos, 1.0f);
      glm::mat4 inverse_translate = glm::inverse(translate);
      auto rotate_matrix = glm::rotate(rotation, glm::vec3(0, 0, 1));
      bottom_left = glm::vec3(translate * rotate_matrix * inverse_translate * glm::vec4(bottom_left,1.0f));
      top_left = glm::vec3(translate * rotate_matrix * inverse_translate * glm::vec4(top_left, 1.0f));
      bottom_right = glm::vec3(translate * rotate_matrix * inverse_translate * glm::vec4(bottom_right, 1.0f));
      top_right = glm::vec3(translate * rotate_matrix * inverse_translate * glm::vec4(top_right, 1.0f));
    }

    float intersection_dist;

    glm::vec2 baryPosition;

    if (glm::intersectRayTriangle(cameraPos, glm::normalize(mouse_world - cameraPos), top_left, bottom_left, bottom_right,
      baryPosition, intersection_dist))
    {
      glm::vec2 point_of_intersection = glm::vec2({0,1}) * (1 - baryPosition.x - baryPosition.y) + glm::vec2({0,0}) * baryPosition.x + glm::vec2({1,0}) * baryPosition.y;
      Data_[intersection_dist].ID = *it;
      Data_[intersection_dist].baryPosition = baryPosition;
      Data_[intersection_dist].uv = point_of_intersection;
    }
    else if (glm::intersectRayTriangle(cameraPos, glm::normalize(mouse_world - cameraPos), top_right, top_left, bottom_right,
          baryPosition, intersection_dist))
    {
      glm::vec2 point_of_intersection = glm::vec2({1,1}) * (1 - baryPosition.x - baryPosition.y) + glm::vec2({0,1}) * baryPosition.x + glm::vec2({1,0}) * baryPosition.y;
      Data_[intersection_dist].ID = *it;
      Data_[intersection_dist].baryPosition = baryPosition;
      Data_[intersection_dist].uv = point_of_intersection;
    }
  }
  PickID();
}

void Picker::PickID()
{
  for (auto it = Data_.begin(); it != Data_.end(); ++it)
  {
    if (CheckPixelData(it->first))
    {
      saved_d = it->first;
      saved_ID = it->second.ID;
      break;
    }
  }
}

glm::vec2 Picker::GetMouseWorld()
{
  return mouse_world;
}

bool Picker::CheckPixelData(float distance)
{
  //const AtlasLayer layer = TextureAtlaser::GetAtlasLayers(chosen_ID);
  //const glm::vec2 uv = TextureAtlaser::GetAtlasUV(chosen_ID);
  //const glm::vec2 scale = TextureAtlaser::GetAtlasScale(chosen_ID);
  //const GLuint textureID = TextureAtlaser::GetTextureID();

  EntityID chosen_ID = Data_[distance].ID;
  
  std::string filePath = TextureComponentManager::getFilePath(chosen_ID);

  if (filePath.empty())
  {
    return true;
  }

  auto raw_data = TextureAtlaser::GetRawData(filePath);
  
  unsigned char* image = raw_data.image;

  //int w, h, c;
  //unsigned char* comp = stbi_load(filePath.c_str(), &w, &h, &c, 0);

  auto bary_y = Data_[distance].uv.y;
  auto bary_x = Data_[distance].uv.x;
  int height = bary_y * raw_data.height;
  int width = bary_x * raw_data.width;

  int offset = (height * raw_data.width + width) * raw_data.channels;
  auto alpha = static_cast<unsigned char>(image[offset + 3]);
  if (alpha > 254)
  {
    return true;
  }

  return false;
}
