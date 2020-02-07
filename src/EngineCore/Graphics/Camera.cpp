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
#include <UWUEngine/Graphics/Camera.h>
#include <UWUEngine/Engine.h>
#include <UWUEngine/Input/InputManager.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <UWUEngine/constants.h>
#include <UWUEngine/FrameRateController.h>
#include <UWUEngine/Graphics/Shader/UniformBufferSystem.h>
#include <UWUEngine/Debugs/TraceLogger.h>

namespace ic = InputConstants;
namespace wc = WindowConstants;
namespace cc = CameraConstants;

glm::vec3 Camera::relative_up;
glm::vec3 Camera::lookAtVector;
glm::vec3 Camera::cameraPos;
glm::vec3 Camera::BackVector;
glm::vec3 Camera::UpVector;
glm::vec3 Camera::RightVector;
glm::vec3 Camera::cameraTarget;
glm::mat4 Camera::projection;
glm::mat4 Camera::view;
float Camera::FOV;
float Camera::nearDistance;
float Camera::farDistance;
float Camera::aspectRatio;
bool Camera::isFirst;
float Camera::Yaw;
float Camera::Pitch;
Camera::state Camera::state_;
bool Camera::switch_;
Camera::lock Camera::lock_;
bool Camera::switch_lock_;
glm::vec2 Camera::mouse_Offset_;

void Camera::Print_Debug_Value()
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

void Camera::calculate_camera_data()
{
  lookAtVector = state_ == state::ENABLE_FPS ? glm::vec3(cos(glm::radians(Yaw)) * cos(glm::radians(Pitch)), sin(glm::radians(Pitch)), sin(glm::radians(Yaw)) * cos(glm::radians(Pitch))) : cameraTarget - cameraPos;
  cameraTarget = state_ == state::ENABLE_FPS ? cameraPos + lookAtVector : cameraTarget = { cameraPos.x, cameraPos.y, -5000.0f };
  BackVector = glm::normalize(glm::vec3(-1) * lookAtVector);
  RightVector = glm::normalize(glm::cross(lookAtVector, relative_up));
  UpVector = glm::cross(BackVector, RightVector);
  projection = glm::perspective(glm::radians(FOV), aspectRatio, nearDistance, farDistance);
  view = glm::lookAt(cameraPos, cameraTarget, UpVector);
}

Camera::Camera()
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
  aspectRatio = WindowManager::getWindowWidth() / WindowManager::getWindowHeight();
  relative_up = { 0.0f,1.0f,0.0f };
  cameraPos = { 0.0f, 0.0f, cc::CAMERA_POSITION };
  cameraTarget = { 0.0f, 0.0f, 0.0f };
  calculate_camera_data();
}

void Camera::Update()
{
  //Print_Debug_Value();
  // sending data to Camera uniform buffer
  UniformBuffer::ShootDataToUniformBuffer(UniformBuffer::Type::Camera);
  moveCamera(1000.0f);
  zoomIn(InputManager::GetScrollWheelVec().y * cc::ZOOM_FACTOR);
  if (InputManager::KeyPressed('M'))
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
    if (InputManager::KeyPressed('N'))
    {
      switch_lock_ = !switch_lock_;
      lock_ = switch_lock_ ? lock::LOCKED : lock::UNLOCKED;
    }
  }
}

void Camera::ResetCameraPosition()
{
  cameraPos.x = 0.f;
  cameraPos.y = 0.f;
  cameraPos.z = cc::CAMERA_POSITION;
}

void Camera::ResetCameraZoom()
{
  FOV = 45.0f;
  projection = glm::perspective(glm::radians(FOV), aspectRatio, nearDistance, farDistance);
}

void Camera::SetCameraPosition(const glm::vec3& new_position)
{
  cameraPos = new_position;
  cameraTarget = glm::vec3(new_position.x, new_position.y, 0.f);
  calculate_camera_data();
}

void Camera::SetCameraPosition(const glm::vec2& new_position)
{
  cameraPos.x = new_position.x;
  cameraPos.y = new_position.y;
  cameraTarget = glm::vec3(new_position.x, new_position.y, 0.f);
  calculate_camera_data();
}

#pragma region Camera Getter
const glm::vec3& Camera::GetCameraPosition()
{
  return cameraPos;
}

const glm::vec3& Camera::GetLookAtVector()
{
  return lookAtVector;
}

const glm::vec3& Camera::GetCameraUp()
{
  return UpVector;
}

const glm::vec3& Camera::GetCameraRight()
{
  return RightVector;
}

const glm::vec3& Camera::GetCameraTarget()
{
  return cameraTarget;
}

const glm::mat4& Camera::GetProjectionMatrix()
{
  return projection;
}

const glm::mat4& Camera::GetViewMatrix()
{
  return view;
}

float Camera::getFOV()
{
  return FOV;
}

float Camera::getNearDistance()
{
  return nearDistance;
}

float Camera::getFarDistance()
{
  return farDistance;
}

float Camera::getAspectRatio()
{
  return aspectRatio;
}

#pragma endregion 
//TODO: set target to player in small box around player

void Camera::SetCameraTarget(const glm::vec3& target)
{
  cameraTarget = target;
  calculate_camera_data();
}

void Camera::zoomIn(float amount)
{
  float dt = FrameRateController::GetConstantDeltaTime<float>();
  FOV = FOV >= 0.f && FOV <= 180.f ? FOV - amount * dt : FOV < 30.f ? FOV + std::abs(amount / 10) * dt : FOV - std::abs(amount / 10) * dt;
  projection = glm::perspective(glm::radians(FOV), aspectRatio, nearDistance, farDistance);
}

void Camera::zoomOut(float amount)
{
  FOV += amount * FrameRateController::GetConstantDeltaTime<float>();
  projection = glm::perspective(glm::radians(FOV), aspectRatio, nearDistance, farDistance);
}

void Camera::moveCamera(float speed)
{
  float dt = FrameRateController::GetConstantDeltaTime<float>();
  cameraPos += state_ == state::DISABLE_FPS || lock_ == lock::LOCKED ? UpVector * speed * dt * (float)(!!InputManager::KeyHeld('W') - !!InputManager::KeyHeld('S')) : lookAtVector * speed * dt * (float)(!!InputManager::KeyHeld('W') - !!InputManager::KeyHeld('S'));
  cameraPos += RightVector * speed * dt * (float)(!!InputManager::KeyHeld('D') - !!InputManager::KeyHeld('A'));
  calculate_camera_data();
}

void Camera::mouseMovement(float xOffSet, float yOffSet)
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

void Camera::setFirstFlag(bool flag)
{
  isFirst = flag;
}

bool Camera::getFirstFlag()
{
  return isFirst;
}

Camera::state Camera::getCameraState()
{
  return state_;
}

glm::vec2 Camera::getMouseOffset()
{
  return mouse_Offset_;
}
