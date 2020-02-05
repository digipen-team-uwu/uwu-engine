/******************************************************************************/
    /*!
    \par        Project Umbra
    \file       WindowManager.h
    \author     Zach Rammell
    \date       2019/09/10
    \brief      GLFW window wrapper

    Copyright © 2019 DigiPen, All rights reserved.
    */
/******************************************************************************/

#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <UWUEngine/BaseSystem.h>

namespace UWUEngine
{

class WindowManager final : public BaseSystem
{
public:
  /* ====== SYSTEM FUNCTIONS ====== */

  WindowManager();
  ~WindowManager();
  //! Swap the window's frame buffer, displaying anything rendered to the back buffer
  void Update() override;

  /* ========= INTERFACE ========== */

  [[nodiscard]]
  GLFWwindow* getWindowHandle() const;

  float getWindowHeight();
  float getWindowWidth();
private:
  /* ======== DATA MEMBERS ======== */

  GLFWwindow* window_ = nullptr;

  /* == IMPLEMENTATION FUNCTIONS == */
  void SetupGLFW();
};

}