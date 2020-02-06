/******************************************************************************/
/*!
\par        Project Umbra
\file       FrameRateController.cpp
\author     Chau Nguyen
\date       2019/09/10
\brief      Controlling frame rate

Copyright � 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#include <UWUEngine/FrameRateController.h>
#include <GLFW/glfw3.h>

namespace UWUEngine
{

FrameRateController::FrameRateController(ISpace* p) : System(p), elapsed_time(0), curr_time(0), delta_time(0), fps(0), paused(false) {}

void FrameRateController::Update()
{
  double fps_calc_interval = 1;
  // get elapsed time (in seconds) between previous and current frames
  static double prev_time = glfwGetTime();
  curr_time = glfwGetTime();
  delta_time = curr_time - prev_time;
  prev_time = curr_time;

  // fps calculations
  static double game_loop_count = 0.0; // number of game loop iterations
  static double start_time = glfwGetTime();
  // get elapsed time since very beginning (in seconds) ...
  elapsed_time = curr_time - start_time;
  ++game_loop_count;
  // update fps at least every 10 seconds ...
  fps_calc_interval = (fps_calc_interval < 0.0) ? 0.0 : fps_calc_interval;
  fps_calc_interval = (fps_calc_interval > 10.0) ? 10.0 : fps_calc_interval;
  if (elapsed_time > fps_calc_interval)
  {
    fps = game_loop_count / elapsed_time;
    start_time = curr_time;
    game_loop_count = 0.0;
  }
}

double FrameRateController::GetFPS() const
{
  return fps;
}

void FrameRateController::SetPaused(bool pause)
{
  paused = pause;
}

} // namespace UWUEngine
