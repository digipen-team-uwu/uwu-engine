/******************************************************************************/
  /*!
  \par        Project Umbra
  \file       Timer.cpp
  \author     Hadi Alhussieni
  \date       2019/12/05
  \brief      Implementation for timers that automatically count down.

  Copyright � 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#include <UWUEngine/Timer.h>
#include <UWUEngine/FrameRateController.h>



std::list<Timer*> TimerManager::timers;

void TimerManager::Update()
{
  for (auto& timer : timers)
    timer->Update();
}

void Timer::Update()
{
  if (running)
    time -= FrameRateController::GetDeltaTime<float>();
}

void Timer::Start() 
{ 
  time = duration;  
  running = true; 
}

void Timer::Stop() 
{ 
  time = duration; 
  running = false; 
}

void Timer::SetDuration(float newDuration)
{
  duration = newDuration;
  time = newDuration;
}
Timer::Timer(float duration) : duration(duration), time(duration), running(true) 
{ 
  TimerManager::timers.push_front(this); 
}

Timer::Timer() : duration(0), time(0), running(false) 
{ 
  TimerManager::timers.push_front(this);
}

Timer::~Timer()
{ 
  TimerManager::timers.remove(this); 
}

bool Timer::Finished()
{
  if (time <= 0 && running)
  {
    time = duration;
    return true;
  }
  return false;
}

bool Timer::Running()
{
    return running;
}