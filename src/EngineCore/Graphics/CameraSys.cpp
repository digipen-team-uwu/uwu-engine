#include <UWUEngine/Systems/CameraSys.h>
#include <UWUEngine/constants.h>
#include <UWUEngine/Systems/LogSys.h>
#include <UWUEngine/Systems/InputSys.h>
#include <UWUEngine/Systems/FrameLimiterSys.h>

using namespace UWUEngine;
namespace ic = InputConstants;
namespace wc = WindowConstants;
namespace cc = CameraConstants;

CameraSys::CameraSys(ISpace* space) : System(space)
{
  lock_ = lock::UNLOCKED;
  switch_lock_ = false;
  switch_ = false;
  state_ = state::DISABLE_FPS;
  isFirst = true;
  Yaw = -90.0f;
  Pitch = 0.0f;
  // initialize
  FOV = 45.0f;
  nearDistance = 5.f;
  farDistance = 100000.f;
  aspectRatio = wc::WINDOW_WIDTH / wc::WINDOW_HEIGHT;
  relative_up = { 0.0f,1.0f,0.0f };
  cameraPos = { 0.0f, 0.0f, cc::CAMERA_POSITION };
  cameraTarget = { 0.0f, 0.0f, 0.0f };
  calculate_camera_data();
}

void CameraSys::Print_Debug_Value()
{
  LogSys& logSys = Get<LogSys>();
  logSys.Log(logSys.DEBUG) <<
    "Field of view: " << FOV << std::endl <<
    "Camera Pos: " << std::endl <<
    "x: " << cameraPos.x << std::endl <<
    "y: " << cameraPos.y << std::endl <<
    "z: " << cameraPos.z << std::endl <<
    "Camera Target: " << std::endl <<
    "x: " << cameraTarget.x << std::endl <<
    "y: " << cameraTarget.y << std::endl <<
    "z: " << cameraTarget.z << std::endl <<
    "Look at Vector: " << std::endl <<
    "x: " << lookAtVector.x << std::endl <<
    "y: " << lookAtVector.y << std::endl <<
    "z: " << lookAtVector.z << std::endl <<
    "Back Vector: " << std::endl <<
    "x: " << BackVector.x << std::endl <<
    "y: " << BackVector.y << std::endl <<
    "z: " << BackVector.z << std::endl;
}

void CameraSys::calculate_camera_data()
{
  lookAtVector = state_ == state::ENABLE_FPS ? glm::vec3(cos(glm::radians(Yaw)) * cos(glm::radians(Pitch)), sin(glm::radians(Pitch)), sin(glm::radians(Yaw)) * cos(glm::radians(Pitch))) : cameraTarget - cameraPos;
  cameraTarget = state_ == state::ENABLE_FPS ? cameraPos + lookAtVector : cameraTarget = { cameraPos.x, cameraPos.y, -5000.0f };
  BackVector = glm::normalize(glm::vec3(-1) * lookAtVector);
  RightVector = glm::normalize(glm::cross(lookAtVector, relative_up));
  UpVector = glm::cross(BackVector, RightVector);
  projection = glm::perspective(glm::radians(FOV), aspectRatio, nearDistance, farDistance);
  view = glm::lookAt(cameraPos, cameraTarget, UpVector);
}

void CameraSys::Update()
{
  InputSys& inputSys = Get<InputSys>();
  //Print_Debug_Value();
  // sending data to Camera uniform buffer
  //UniformBuffer::ShootDataToUniformBuffer(UniformBuffer::Type::CameraSys);
  moveCamera(1500.0f);
  zoomIn(inputSys.GetScrollWheelVec().y * cc::ZOOM_FACTOR);
  if (inputSys.KeyPressed('M'))
  {
    switch_ = !switch_;
    state_ = switch_ ? state::ENABLE_FPS : state::DISABLE_FPS;
    if (state_ == state::DISABLE_FPS)
    {
      lock_ = lock::UNLOCKED;
      switch_lock_ = false;
      ResetCameraPosition();
      ResetCameraZoom();
    }
  }
  if (state_ == state::ENABLE_FPS)
  {
    if (inputSys.KeyPressed('N'))
    {
      switch_lock_ = !switch_lock_;
      lock_ = switch_lock_ ? lock::LOCKED : lock::UNLOCKED;
    }
  }
}

void CameraSys::ResetCameraPosition()
{
  cameraPos.x = 0.f;
  cameraPos.y = 0.f;
  cameraPos.z = cc::CAMERA_POSITION;
}

void CameraSys::ResetCameraZoom()
{
  FOV = 45.0f;
  projection = glm::perspective(glm::radians(FOV), aspectRatio, nearDistance, farDistance);
}

void CameraSys::SetCameraPosition(const glm::vec3& new_position)
{
  cameraPos = new_position;
  cameraTarget = glm::vec3(new_position.x, new_position.y, 0.f);
  calculate_camera_data();
}

void CameraSys::SetCameraPosition(const glm::vec2& new_position)
{
  cameraPos.x = new_position.x;
  cameraPos.y = new_position.y;
  cameraTarget = glm::vec3(new_position.x, new_position.y, 0.f);
  calculate_camera_data();
}

#pragma region Camera Getter
const glm::vec3& CameraSys::GetCameraPosition()
{
  return cameraPos;
}

const glm::vec3& CameraSys::GetLookAtVector()
{
  return lookAtVector;
}

const glm::vec3& CameraSys::GetCameraUp()
{
  return UpVector;
}

const glm::vec3& CameraSys::GetCameraRight()
{
  return RightVector;
}

const glm::vec3& CameraSys::GetCameraTarget()
{
  return cameraTarget;
}

const glm::mat4& CameraSys::GetProjectionMatrix()
{
  return projection;
}

const glm::mat4& CameraSys::GetViewMatrix()
{
  return view;
}

float CameraSys::getFOV()
{
  return FOV;
}

float CameraSys::getNearDistance()
{
  return nearDistance;
}

float CameraSys::getFarDistance()
{
  return farDistance;
}

float CameraSys::getAspectRatio()
{
  return aspectRatio;
}

#pragma endregion 
//TODO: set target to player in small box around player

void CameraSys::SetCameraTarget(const glm::vec3& target)
{
  cameraTarget = target;
  calculate_camera_data();
}

void CameraSys::zoomIn(float amount)
{
  float dt = Get<FrameLimiterSys>().GetConstantDeltaTime<float>();
  //FOV = FOV >= 0.f && FOV <= 180.f ? FOV - amount * dt : FOV < 30.f ? FOV + std::abs(amount / 10) * dt : FOV - std::abs(amount / 10) * dt;
  //projection = glm::perspective(glm::radians(FOV), aspectRatio, nearDistance, farDistance);
  cameraPos.z += amount * 20.f * dt;
}

void CameraSys::zoomOut(float amount)
{
  FOV += amount * Get<FrameLimiterSys>().GetConstantDeltaTime<float>();
  projection = glm::perspective(glm::radians(FOV), aspectRatio, nearDistance, farDistance);
}

void CameraSys::moveCamera(float speed)
{
  float dt = Get<FrameLimiterSys>().GetConstantDeltaTime<float>();
  cameraPos += state_ == state::DISABLE_FPS || lock_ == lock::LOCKED ? UpVector * speed * dt * (float)(!!Get<InputSys>().KeyHeld('W') - !!Get<InputSys>().KeyHeld('S')) : lookAtVector * speed * dt * (float)(!!Get<InputSys>().KeyHeld('W') - !!Get<InputSys>().KeyHeld('S'));
  cameraPos += RightVector * speed * dt * (float)(!!Get<InputSys>().KeyHeld('D') - !!Get<InputSys>().KeyHeld('A'));
  calculate_camera_data();
}

void CameraSys::mouseMovement(float xOffSet, float yOffSet)
{
  float x_offset = xOffSet * cc::MOUSE_SENSITIVITY;
  float y_offset = yOffSet * cc::MOUSE_SENSITIVITY;

  mouse_Offset_ = { x_offset, y_offset };

  if (state_ == state::ENABLE_FPS)
  {
    if (lock_ == lock::UNLOCKED)
    {
      Yaw += mouse_Offset_.x;
      Pitch += mouse_Offset_.y;

      Pitch = Pitch > 89.0f ? 89.0f : Pitch;
      Pitch = Pitch < -89.0f ? -89.0f : Pitch;

      calculate_camera_data();
    }
  }
}

void CameraSys::setFirstFlag(bool flag)
{
  isFirst = flag;
}

bool CameraSys::getFirstFlag()
{
  return isFirst;
}

CameraSys::state CameraSys::getCameraState()
{
  return state_;
}

glm::vec2 CameraSys::getMouseOffset()
{
  return mouse_Offset_;
}