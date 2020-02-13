/******************************************************************************/
  /*!
  \par        Project Umbra
  \file       Timer.cpp
  \author     Hadi Alhussieni
  \date       2019/12/05
  \brief      Implementation for timers that automatically count down.

  Copyright (c) 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#include <UWUEngine/Systems/TimerSys.h>
#include <UWUEngine/Systems/FrameLimiterSys.h>

namespace UWUEngine
{
TimerSys::TimerSys(ISpace* p) : System(p) {}

void TimerSys::Update()
{
  for (auto& timer : timers)
    timer->Update();
}

void TimerSys::Timer::Update()
{
  if (running)
  {
    time -= parent.Get<FrameLimiterSys>().GetDeltaTime<float>();
  }
}

void TimerSys::Timer::Start()
{
  time = duration;
  running = true;
}

void TimerSys::Timer::Stop()
{
  time = duration;
  running = false;
}

void TimerSys::AddTimer(Timer* t)
{
  timers.push_front(t);
}

void TimerSys::RemoveTimer(Timer* t)
{
  timers.remove(t);
}

void TimerSys::Timer::SetDuration(float newDuration)
{
  duration = newDuration;
  time = newDuration;
}
TimerSys::Timer::Timer(TimerSys& p, float duration) : duration(duration), time(duration), running(true), parent(p)
{
  parent.AddTimer(this);
}

TimerSys::Timer::~Timer()
{
  parent.RemoveTimer(this);
}

bool TimerSys::Timer::Finished()
{
  if (time <= 0 && running)
  {
    time = duration;
    return true;
  }
  return false;
}

bool TimerSys::Timer::Running() const
{
  return running;
}

} //namespace UWUEngine
