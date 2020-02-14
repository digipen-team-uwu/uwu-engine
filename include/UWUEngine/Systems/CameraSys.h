#pragma once

#include <UWUEngine/System.h>
#include <glm/gtx/transform.hpp>

namespace UWUEngine
{
  class CameraSys : public System
  {
  public:
    CameraSys(ISpace* space);
    ~CameraSys() override = default;
    void Update() override;

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

    void ResetCameraPosition();
    void ResetCameraZoom();
    void SetCameraPosition(const glm::vec3& new_position);
    void SetCameraPosition(const glm::vec2& new_position);
    const glm::vec3& GetCameraPosition();

    const glm::vec3& GetLookAtVector();

    const glm::vec3& GetCameraUp();

    const glm::vec3& GetCameraRight();
    void SetCameraTarget(const glm::vec3& target);
    const glm::vec3& GetCameraTarget();
    const glm::mat4& GetProjectionMatrix();
    const glm::mat4& GetViewMatrix();
    void zoomIn(float amount);
    void zoomOut(float amount);
    void moveCamera(float speed);
    float getFOV();
    float getNearDistance();
    float getFarDistance();
    float getAspectRatio();
    void mouseMovement(float xOffSet, float yOffSet);
    void setFirstFlag(bool flag);
    bool getFirstFlag();
    state getCameraState();
    glm::vec2 getMouseOffset();

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
    glm::vec2 mouse_Offset_;
  };
}