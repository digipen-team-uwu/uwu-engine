#pragma once

#include <UWUEngine/System.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace UWUTest
{

 /* DOES NOT SUPPORT RENDERING */
class HeadlessWindowSys : public UWUEngine::System
{
public:
  /* ====== SYSTEM FUNCTIONS ====== */

  HeadlessWindowSys(UWUEngine::ISpace* p) : System(p)
  {
    glfwInit();
  }

  ~HeadlessWindowSys()
  {
    glfwTerminate();
  }

  void Update() override {}

};

}
