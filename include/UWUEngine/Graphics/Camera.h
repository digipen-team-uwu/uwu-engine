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
#include <UWUEngine/BaseSystem.h>

class Camera : public BaseSystem<Camera>
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
    
    Camera();
    void Update() override;
    ~Camera() = default;

    static void ResetCameraPosition();
    static void ResetCameraZoom();
    static void SetCameraPosition(const glm::vec3& new_position);
    static void SetCameraPosition(const glm::vec2& new_position);
    static const glm::vec3& GetCameraPosition();
    //void SetCameraFront(const glm::vec3& front);
    static const glm::vec3& GetLookAtVector();
    //void SetCameraUp(const glm::vec3& Up);
    static const glm::vec3& GetCameraUp();
    //void SetCameraRight(const glm::vec3& right);
    static const glm::vec3& GetCameraRight();
    static void SetCameraTarget(const glm::vec3& target);
    static const glm::vec3& GetCameraTarget();
    static const glm::mat4& GetProjectionMatrix();
    static const glm::mat4& GetViewMatrix();
    static void zoomIn(float amount);
    static void zoomOut(float amount);
    static void moveCamera(float speed);
    static float getFOV();
    static float getNearDistance();
    static float getFarDistance();
    static float getAspectRatio();
    static void mouseMovement(float xOffSet, float yOffSet);
    static void setFirstFlag(bool flag);
    static bool getFirstFlag();
    static state getCameraState();
private:
    static void Print_Debug_Value();
    static void calculate_camera_data();
    static glm::vec3 relative_up;
    static glm::vec3 lookAtVector;
    static glm::vec3 cameraPos;
    static glm::vec3 BackVector;
    static glm::vec3 UpVector;
    static glm::vec3 RightVector;
    static glm::vec3 cameraTarget;
    static glm::mat4 projection;
    static glm::mat4 view;
    static float FOV;
    static float nearDistance;
    static float farDistance;
    static float aspectRatio;
    static bool isFirst;
    static float Yaw;
    static float Pitch;
    static state state_;
    static bool switch_;
    static lock lock_;
    static bool switch_lock_;
};
