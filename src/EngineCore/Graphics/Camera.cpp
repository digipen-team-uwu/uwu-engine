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
#include <UWUEngine/Helper.h>
#include <UWUEngine/FrameRateController.h>
#include <UWUEngine/Graphics/Shader/UniformBufferSystem.h>
#include <iostream>

namespace ic = InputConstants;
namespace wc = WindowConstants;
namespace cc = CameraConstants;

glm::vec3 Camera::cameraPos;
glm::vec3 Camera::cameraFront;
glm::vec3 Camera::cameraUp;
glm::vec3 Camera::cameraRight;
glm::vec3 Camera::cameraTarget;
glm::mat4 Camera::projection;
glm::mat4 Camera::view;

template<>
int RegisterSystemHelper<Camera>::RegisterSystemHelper_ID = SystemUpdater::AddSystem<Camera>(SystemInitOrder::FIRST, SystemUpdateOrder::Camera);

void Camera::calculate_camera_vector()
{
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    cameraFront = glm::normalize(cameraTarget - cameraPos);
    cameraRight = glm::normalize(glm::cross(up, cameraFront));
    cameraUp = glm::cross(cameraFront, cameraRight);
}

Camera::Camera()
{
    // initialize
    cameraPos = glm::vec3(0.0f, 0.0f, cc::CAMERA_POSITION);
    cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    calculate_camera_vector();
    projection = glm::perspective(glm::radians(45.0f),
        static_cast<float>(wc::WINDOW_WIDTH) / static_cast<float>(wc::WINDOW_HEIGHT),
		.1f, 100000.f);
}

void Camera::Update()
{
    //std::cout << "pos x: " << cameraPos.x << std::endl;
    //std::cout << "pos y: " << cameraPos.y << std::endl;
    //std::cout << "pos z: " << cameraPos.z << std::endl;
    // calculate view matrix
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    // sending data to Camera uniform buffer
    UniformBuffer::ShootDataToUniformBuffer(UniformBuffer::Type::Camera);
    moveCamera(cameraPos.z >= 5.f ? cameraPos.z : 5);

    zoomIn(InputManager::GetScrollWheelVec().y * cc::ZOOM_FACTOR);
}

void Camera::ResetCameraPosition()
{
  cameraPos.x = 0.f;
  cameraPos.y = 0.f;
  cameraPos.z = cc::CAMERA_POSITION;
}

void Camera::ResetCameraZoom()
{
  cameraPos.z = cc::CAMERA_POSITION;
}

void Camera::SetCameraPosition(const glm::vec3& new_position)
{
    cameraPos = new_position;
    cameraTarget = glm::vec3(new_position.x, new_position.y, 0.f);
    calculate_camera_vector();
}

void Camera::SetCameraPosition(const glm::vec2& new_position)
{
  cameraPos.x = new_position.x;
  cameraPos.y = new_position.y;
  cameraTarget = glm::vec3(new_position.x, new_position.y, 0.f);
  calculate_camera_vector();
}

const glm::vec3& Camera::GetCameraPosition()
{
    return cameraPos;
}

const glm::vec3& Camera::GetCameraFront()
{
    return cameraFront;
}

const glm::vec3& Camera::GetCameraUp()
{
    return cameraUp;
}

const glm::vec3& Camera::GetCameraRight()
{
    return cameraRight;
}

//TODO: set target to player in small box around player

void Camera::SetCameraTarget(const glm::vec3& target)
{
    cameraTarget = target;
    calculate_camera_vector();
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

void Camera::zoomIn(float amount)
{
    cameraPos.z -= amount;
}

void Camera::zoomOut(float amount)
{
    cameraPos.z += amount;
}

void Camera::moveCamera(float speed)
{
    float dt = FrameRateController::GetDeltaTime<float>();
    cameraPos += cameraUp * speed * dt * (float)(!!InputManager::KeyHeld('W') - !!InputManager::KeyHeld('S'));
    cameraPos += cameraRight * speed * dt * (float)(!!InputManager::KeyHeld('A') - !!InputManager::KeyHeld('D'));;
}
