/******************************************************************************/
    /*!
    \par        Project Umbra
    \file       WindowManager.h
    \author     Zach Rammell
    \date       2019/09/10
    \brief      SDL window wrapper

    Copyright � 2019 DigiPen, All rights reserved.
    */
/******************************************************************************/

#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <UWUEngine/BaseSystem.h>

class WindowManager : public BaseSystem<WindowManager>
{
public:
  WindowManager();
  ~WindowManager();
  [[nodiscard]]
  static GLFWwindow* getWindowHandle();
	//! Swap the window's frame buffer, displaying anything rendered to the back buffer
	void Update();
private:
	static inline GLFWwindow* window_ = nullptr;
};

