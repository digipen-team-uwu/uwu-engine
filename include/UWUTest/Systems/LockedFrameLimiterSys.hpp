#pragma once

#include <UWUEngine/System.h>

namespace UWUTest
{

template<unsigned FPS>
class LockedFrameLimiterSys : public UWUEngine::System
{
public:
  /* ====== SYSTEM FUNCTIONS ====== */

  LockedFrameLimiterSys(UWUEngine::ISpace* p) : System(p) {}

  ~LockedFrameLimiterSys() = default;

  void Update() override {}

  template<typename T>
  T GetDeltaTime()
  {
    if (paused)
    {
      return 0.0f;
    }
    return static_cast<T>(delta_time);
  }

  template<typename T>
  T GetConstantDeltaTime()
  {
    return static_cast<T>(delta_time);
  }

  double GetFPS() const
  {
    return fps;
  }

  void SetPaused(bool pause)
  {
    paused = pause;
  }

private:
  const double elapsed_time = 0.0;
  const double curr_time = 0.0;
  const double delta_time = 1 / static_cast<double>(FPS);
  const double fps = static_cast<double>(FPS);
  bool paused = false;

};

}
