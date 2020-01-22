/******************************************************************************/
    /*!
    \par        Project Umbra
    \file       WindowManager.cpp
    \author     Zach Rammell
    \date       2019/09/10
    \brief      SDL window wrapper implementation

    Copyright � 2019 DigiPen, All rights reserved.
    */
/******************************************************************************/

#include <UWUEngine/WindowManager.h>
#include <UWUEngine/constants.h>
#include <iostream>
#include <UWUEngine/Debugs/TraceLogger.h>
// for access to OpenGL API declarations

namespace wc = WindowConstants;



WindowManager::WindowManager()
{
    TraceLogger::Log(TraceLogger::Severity::INFO) << "init window manager\n";

  if (glfwInit() == GLFW_FALSE)
  {
    //TODO: add error handling for glfw initialization
    const char** buffer;
    glfwGetError(buffer);
    TraceLogger::Log(TraceLogger::FAILURE) << "COULD NOT INITIALIZE GLFW!" << std::string(*buffer) << std::endl;
    return;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  // disable deprecated code
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
  glfwWindowHint(GLFW_RED_BITS, 8);
  glfwWindowHint(GLFW_GREEN_BITS, 8);
  glfwWindowHint(GLFW_BLUE_BITS, 8);
  glfwWindowHint(GLFW_ALPHA_BITS, 8);
#ifdef _DEBUG
  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
#else
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
#endif
  glfwWindowHint(GLFW_DEPTH_BITS, 32);

  window_ = glfwCreateWindow(wc::WINDOW_WIDTH, wc::WINDOW_HEIGHT, "uwuENGINE", NULL, NULL);

  if (window_ == nullptr)
  {
    //TODO: add error handling for window opening
    const char** buffer;
    glfwGetError(buffer);
    TraceLogger::Log(TraceLogger::FAILURE) << "Window Not Opened Properly!" << std::string(*buffer) << std::endl;
    return;
  }

  glfwMakeContextCurrent(window_);

  // makes buffer swap synchronized with the monitor's vertical refresh
  glfwSwapInterval(1);

  GLenum err = glewInit();
  if (GLEW_OK != err)
  {
    TraceLogger::Log(TraceLogger::FAILURE) << "Unable to initialize GLEW - error: "
      << glewGetErrorString(err) << " abort program" << std::endl;
  }
  if (GLEW_VERSION_4_5)
  {
    TraceLogger::Log(TraceLogger::INFO) << "Using glew version: " << glewGetString(GLEW_VERSION) << std::endl;
    TraceLogger::Log(TraceLogger::INFO) << "Driver supports OpenGL 4.5" << std::endl;
  }
  else
  {
    // TODO: add error handling for GLEW error
    TraceLogger::Log(TraceLogger::FAILURE) << "Driver doesn't support OpenGL 4.5 - abort program" << std::endl;
    return;
  }
}

WindowManager::~WindowManager()
{
  glfwDestroyWindow(window_);
  glfwTerminate();
}

GLFWwindow* WindowManager::getWindowHandle()
{
	return window_;
}

float WindowManager::getWindowHeight()
{
  return static_cast<float>(WindowConstants::WINDOW_HEIGHT);
}

float WindowManager::getWindowWidth()
{
  return static_cast<float>(WindowConstants::WINDOW_WIDTH);
}

void WindowManager::Update()
{
  glfwSwapBuffers(window_);
}
