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

template<>
int RegisterSystemHelper<FrameRateController>::RegisterSystemHelper_ID = SystemUpdater::AddSystem<FrameRateController>(SystemInitOrder::FIRST, SystemUpdateOrder::FrameRate);

double FrameRateController::elapsed_time;
double FrameRateController::curr_time;
double FrameRateController::delta_time;
double FrameRateController::fps;
bool FrameRateController::paused;

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
    if (elapsed_time > fps_calc_interval) {
        fps = game_loop_count / elapsed_time;
        start_time = curr_time;
        game_loop_count = 0.0;
    }
}

double FrameRateController::GetFPS()
{
    return fps;
}

void FrameRateController::SetPaused(bool pause)
{
    paused = pause;
}


/////////////////////////////////////////////////////////////
//////////////////////DEPRECATED CODE////////////////////////
/////////////////////////////////////////////////////////////
/*void FrameRateController::StartUp()
{
    Reset();
    timeScale = 1.0f;
}


void FrameRateController::Reset()
{
    startTicks = SDL_GetTicks();
    elapsedTicks = 0;
    deltaTime = 0.0f;
}

void FrameRateController::Update()
{
    elapsedTicks = SDL_GetTicks() - startTicks;
    deltaTime = elapsedTicks * 0.01f;
    fps = 1.0f / deltaTime;
}


void FrameRateController::SetTimeScale(float timeScale_)
{
    timeScale = timeScale_;
}

const float FrameRateController::GetTimeScale() const
{
    return timeScale;
}

const float FrameRateController::GetDeltaTime() const
{
    return deltaTime;
}

const float FrameRateController::GetFps() const
{
    return fps;
}*/

