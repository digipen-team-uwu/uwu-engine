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
#pragma once
#include <glm/glm.hpp>
#include <UWUEngine/System.h>

namespace UWUEngine
{

class CameraSys : public System
{
public:

  enum class state
  {
    ENABLE_FPS,
    DISABLE_FPS,

    Total
  };

  enum class lock
  {
    LOCKED,
    UNLOCKED,

    Total
  };

  CameraSys(ISpace*);
  void Update() override;
  ~CameraSys() = default;

  void ResetPosition();
  void ResetZoom();
  void SetPosition(const glm::vec3& new_position);
  void SetPosition(const glm::vec2& new_position);
  const glm::vec3& GetPosition() const;
  //void SetCameraFront(const glm::vec3& front);
  const glm::vec3& GetLookAtVector() const;
  //void SetCameraUp(const glm::vec3& Up);
  const glm::vec3& GetUp() const;
  //void SetCameraRight(const glm::vec3& right);
  const glm::vec3& GetRight() const;
  void SetTarget(const glm::vec3& target);
  const glm::vec3& GetTarget() const;
  const glm::mat4& GetProjectionMatrix() const;
  const glm::mat4& GetViewMatrix() const;
  void zoomIn(float amount);
  void zoomOut(float amount);
  void move(float speed);
  float getFOV() const;
  float getNearDistance() const;
  float getFarDistance() const;
  float getAspectRatio() const;
  void mouseMovement(float xOffSet, float yOffSet);
  void setFirstFlag(bool flag);
  bool getFirstFlag();
  state getState() const;
private:
  void Print_Debug_Value();
  void calculate_camera_data();
  glm::vec3 relative_up;
  glm::vec3 lookAtVector;
  glm::vec3 cameraPos;
  glm::vec3 BackVector;
  glm::vec3 UpVector;
  glm::vec3 RightVector;
  glm::vec3 cameraTarget;
  glm::mat4 projection;
  glm::mat4 view;
  float FOV;
  float nearDistance;
  float farDistance;
  float aspectRatio;
  bool isFirst;
  float Yaw;
  float Pitch;
  state state_;
  bool switch_;
  lock lock_;
  bool switch_lock_;
};

}
