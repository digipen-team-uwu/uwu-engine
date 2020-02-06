/******************************************************************************/
    /*!
    \par        Project Umbra
    \file       WindowSys.cpp
    \author     Zach Rammell
    \date       2019/09/10
    \brief      GLFW window wrapper implementation

    Copyright © 2019 DigiPen, All rights reserved.
    */
/******************************************************************************/

#include <UWUEngine/WindowSys.h>
#include <UWUEngine/constants.h>
#include <UWUEngine/Debugs/TraceLogger.h>
#include <UWUEngine/Debugs/SystemException.h>

namespace wc = WindowConstants;

/* ======== HELPER FUNCTION DECLARATIONS ======= */
namespace
{
void setup_glew();
void setup_hints() noexcept;
}

namespace UWUEngine
{

WindowSys::WindowSys(ISpace* p) : System(p)
{
  SetupGLFW();
  setup_glew();
}

WindowSys::~WindowSys()
{
  glfwDestroyWindow(window_);
  glfwTerminate();
}

void WindowSys::Update()
{
  glfwSwapBuffers(window_);
}

GLFWwindow* WindowSys::getWindowHandle() const
{
  return window_;
}

void WindowSys::SetupGLFW()
{
  if (glfwInit() == GLFW_FALSE)
  {
    const char** buffer;
    const auto error = glfwGetError(buffer);
    if (error)
    {
      TraceLogger::Log(TraceLogger::FAILURE) << "COULD NOT INITIALIZE GLFW! " << std::string(*buffer) << std::endl;
      throw SystemStartupException<WindowSys>();
    }
  }

  setup_hints();

  window_ = glfwCreateWindow(wc::WINDOW_WIDTH, wc::WINDOW_HEIGHT, "uwuENGINE", nullptr, nullptr);

  if (window_ == nullptr)
  {
    const char** buffer;
    glfwGetError(buffer);
    TraceLogger::Log(TraceLogger::FAILURE) << "Window Not Opened Properly!" << std::string(*buffer) << std::endl;
    throw SystemStartupException<WindowSys>();
  }

  glfwMakeContextCurrent(window_);

  // makes buffer swap synchronized with the monitor's vertical refresh
  glfwSwapInterval(1);
}

} // namespace UWUEngine

/* ====== HELPER FUNCTION IMPLEMENTATIONS ====== */
namespace
{

void setup_glew()
{
  const auto err = glewInit();
  if (GLEW_OK != err)
  {
    TraceLogger::Log(TraceLogger::FAILURE) << "Unable to initialize GLEW - error: "
      << glewGetErrorString(err) << std::endl;
    throw SystemStartupException<UWUEngine::WindowSys>();
  }
  if (GLEW_VERSION_4_5)
  {
    TraceLogger::Log(TraceLogger::INFO) << "Using GLEW version: " << glewGetString(GLEW_VERSION) << std::endl;
    TraceLogger::Log(TraceLogger::INFO) << "Driver supports OpenGL 4.5" << std::endl;
  }
  else
  {
    TraceLogger::Log(TraceLogger::FAILURE) << "Driver doesn't support OpenGL 4.5" << std::endl;
    throw SystemStartupException<UWUEngine::WindowSys>();
  }
}

void setup_hints() noexcept
{
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
}

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
