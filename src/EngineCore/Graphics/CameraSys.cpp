/******************************************************************************/
/*!
\par        Project Umbra
\file       Camera.cpp
\author     Chau Nguyen
\date       2019/09/27
\brief      Managing camera

Copyright 2019 DigiPen, All rights reserved.

*/
/******************************************************************************/
#include <UWUEngine/Graphics/CameraSys.h>
#include <UWUEngine/Engine.h>
#include <UWUEngine/Input/InputManager.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <UWUEngine/constants.h>
#include <UWUEngine/Graphics/Shader/UniformBufferSystem.h>
#include <UWUEngine/Debugs/TraceLogger.h>
#include <UWUEngine/WindowSys.h>
#include <UWUEngine/FrameLimiterSys.h>

namespace ic = InputConstants;
namespace wc = WindowConstants;
namespace cc = CameraConstants;

namespace UWUEngine
{

void CameraSys::Print_Debug_Value()
{
  TraceLogger::Log(TraceLogger::DEBUG) <<
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

CameraSys::CameraSys(ISpace* p) : System(p)
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
  aspectRatio = Get<WindowSys>().getWindowWidth() / Get<WindowSys>().getWindowHeight();
  relative_up = { 0.0f,1.0f,0.0f };
  cameraPos = { 0.0f, 0.0f, cc::CAMERA_POSITION };
  cameraTarget = { 0.0f, 0.0f, 0.0f };
  calculate_camera_data();
}

void CameraSys::Update()
{
  //Print_Debug_Value();
  // sending data to Camera uniform buffer
  UniformBuffer::ShootDataToUniformBuffer(UniformBuffer::Type::Camera);
  move(1000.0f);
  zoomIn(InputManager::GetScrollWheelVec().y * cc::ZOOM_FACTOR);
  if (InputManager::KeyPressed('M'))
  {
    switch_ = !switch_;
    state_ = switch_ ? state::ENABLE_FPS : state::DISABLE_FPS;
    if (state_ == state::DISABLE_FPS)
    {
      lock_ = lock::UNLOCKED;
      switch_lock_ = false;
      ResetPosition();
      ResetZoom();
    }
  }
  if (state_ == state::ENABLE_FPS)
  {
    if (InputManager::KeyPressed('N'))
    {
      switch_lock_ = !switch_lock_;
      lock_ = switch_lock_ ? lock::LOCKED : lock::UNLOCKED;
    }
  }
}

void CameraSys::ResetPosition()
{
  cameraPos.x = 0.f;
  cameraPos.y = 0.f;
  cameraPos.z = cc::CAMERA_POSITION;
}

void CameraSys::ResetZoom()
{
  FOV = 45.0f;
  projection = glm::perspective(glm::radians(FOV), aspectRatio, nearDistance, farDistance);
}

void CameraSys::SetPosition(const glm::vec3& new_position)
{
  cameraPos = new_position;
  cameraTarget = glm::vec3(new_position.x, new_position.y, 0.f);
  calculate_camera_data();
}

void CameraSys::SetPosition(const glm::vec2& new_position)
{
  cameraPos.x = new_position.x;
  cameraPos.y = new_position.y;
  cameraTarget = glm::vec3(new_position.x, new_position.y, 0.f);
  calculate_camera_data();
}

#pragma region Camera Getter
const glm::vec3& CameraSys::GetPosition() const
{
  return cameraPos;
}

const glm::vec3& CameraSys::GetLookAtVector() const
{
  return lookAtVector;
}

const glm::vec3& CameraSys::GetUp() const
{
  return UpVector;
}

const glm::vec3& CameraSys::GetRight() const
{
  return RightVector;
}

const glm::vec3& CameraSys::GetTarget() const
{
  return cameraTarget;
}

const glm::mat4& CameraSys::GetProjectionMatrix() const
{
  return projection;
}

const glm::mat4& CameraSys::GetViewMatrix() const
{
  return view;
}

float CameraSys::getFOV() const
{
  return FOV;
}

float CameraSys::getNearDistance() const
{
  return nearDistance;
}

float CameraSys::getFarDistance() const
{
  return farDistance;
}

float CameraSys::getAspectRatio() const
{
  return aspectRatio;
}

#pragma endregion

void CameraSys::SetTarget(const glm::vec3& target)
{
  cameraTarget = target;
  calculate_camera_data();
}

void CameraSys::zoomIn(float amount)
{
  const float dt = Get<FrameLimiterSys>().GetDeltaTime<float>();
  FOV = FOV >= 30.f && FOV <= 90.f ? FOV - amount * dt : FOV < 30.f ? FOV + std::abs(amount / 10) * dt : FOV - std::abs(amount / 10) * dt;
  projection = glm::perspective(glm::radians(FOV), aspectRatio, nearDistance, farDistance);
}

void CameraSys::zoomOut(float amount)
{
  float dt = Get<FrameLimiterSys>().GetDeltaTime<float>();
  FOV += amount * dt;
  projection = glm::perspective(glm::radians(FOV), aspectRatio, nearDistance, farDistance);
}

void CameraSys::move(float speed)
{
  float dt = Get<FrameLimiterSys>().GetConstantDeltaTime<float>();
  cameraPos += state_ == state::DISABLE_FPS || lock_ == lock::LOCKED ? UpVector * speed * dt * static_cast<float>(!!InputManager::KeyHeld('W') - !!InputManager::KeyHeld('S')) : lookAtVector * speed * dt * static_cast<float>(!!InputManager::KeyHeld('W') - !!InputManager::KeyHeld('S'));
  cameraPos += RightVector * speed * dt * static_cast<float>(!!InputManager::KeyHeld('D') - !!InputManager::KeyHeld('A'));
  calculate_camera_data();
}

void CameraSys::mouseMovement(float xOffSet, float yOffSet)
{
  if (state_ == state::ENABLE_FPS)
  {
    if (lock_ == lock::UNLOCKED)
    {
      const float x_offset = xOffSet * cc::MOUSE_SENSITIVITY;
      const float y_offset = yOffSet * cc::MOUSE_SENSITIVITY;

      Yaw += x_offset;
      Pitch += y_offset;

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

CameraSys::state CameraSys::getState() const
{
  return state_;
}

}