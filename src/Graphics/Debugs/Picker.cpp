#include <UWUEngine/Graphics/Debugs/Picker.h>
#include <UWUEngine/Input/InputManager.h>
#include <UWUEngine/Graphics/Camera.h>
#include <UWUEngine/constants.h>
#include <UWUEngine/WindowManager.h>
#include <UWUEngine/Component/TransformComponentManager.h>

Picker::Picker()
{
  saved_t = 1000.f;
  saved_ID = static_cast<unsigned>(-1);
}

EntityID Picker::Pick()
{
  glm::vec3 mousePos = glm::vec3(InputManager::GetMousePos(),1.0f);

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
  float width_vf = Camera::getAspectRatio() * height_vf;

  glm::mat3 ndc_to_vf(1.0f);
  ndc_to_vf[0].x = width_vf / 2.0f;
  ndc_to_vf[1].y = height_vf / 2.0f;
  ndc_to_vf[2].x = 0.0f;
  ndc_to_vf[2].y = 0.0f;
  ndc_to_vf[2].z = 1.0f;
#pragma endregion 

#pragma region convert view finder to view frame
  glm::vec3 P_vf = ndc_to_vf * vp_to_ndc * GLFW_to_vp * mousePos;
  glm::vec4 P_view = { P_vf.x, P_vf.y, -1 * nearDist, 1.f };
#pragma endregion 

#pragma region convert view frame to world
  glm::mat4 view_to_world = glm::inverse(Camera::GetViewMatrix());
  glm::vec3 P_world = glm::vec3(view_to_world * P_view);
#pragma endregion 

  glm::vec3 cameraPos = Camera::GetCameraPosition();

  // get a list of current active objects
  auto ids = EntityManager::GetIDs();

  for (auto it = ids.begin(); it != ids.end(); ++it)
  {
    // get object current position in world coord
    glm::vec3 objectPos = glm::vec3(TransformComponentManager::GetTranslation(*it));

    glm::vec3 scale = TransformComponentManager::GetScale(*it);

    float r = glm::max(glm::max(scale.x, scale.y), scale.z);
    float r_square = r * r;

    // ray form: r(t) = cameraPos + t * (P_world - cameraPos)
    glm::vec3 q = P_world - cameraPos;            // P_W - E_W
    glm::vec3 cam_to_obj = objectPos - cameraPos; // C_W - E_W
    glm::vec3 mouse_to_obj = objectPos - P_world; // C_W - P_W
    float p = glm::dot(objectPos - cameraPos,q);
    float m = p / q.length();
    float len = cam_to_obj.length();
    float n_square = cam_to_obj.length() * cam_to_obj.length() - (m * m);

    if (glm::dot(cam_to_obj, cam_to_obj) <= r_square &&
        glm::dot(mouse_to_obj, mouse_to_obj) <= r_square)
    {
      // trivial acceptance
      return *it;
    }

    // camera is outside of sphere
    if (glm::dot(cam_to_obj, cam_to_obj) > r_square)
    {
      // ray is moving away from sphere
      if (p < 0)
      {
        continue;
      }
      // ray is moving toward sphere but will miss it
      if (m > 0 && n_square > r_square)
      {
        continue;
      }
      // ray intersects with sphere
      float s = sqrtf(r_square - n_square);
      float t_e = m - s;
      float t = t_e / q.length();
      if (t < saved_t)
      {
        saved_t = t;
        saved_ID = *it;
      }
    }
  }

  return saved_ID;
}
