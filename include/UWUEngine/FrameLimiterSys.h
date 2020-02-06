/******************************************************************************/
/*!
\par        Project Umbra
\file       FrameRateController.h
\author     Chau Nguyen
\date       2019/09/10
\brief      Controlling frame rate

Copyright � 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#pragma once
#include <UWUEngine/System.h>

namespace UWUEngine
{

class FrameLimiterSys : public System
{
public:
  FrameLimiterSys(ISpace*);
  ~FrameLimiterSys() = default;

  template<typename T>
  T GetDeltaTime()
  {
    if (paused)
    {
      return 0.0f;
    }
    return static_cast<T>((delta_time > .25f) ? 0.016666666667f : delta_time);
  }
  template<typename T>
  T GetConstantDeltaTime()
  {
    return static_cast<T>((delta_time > .25f) ? 0.016666666667f : delta_time);
  }
  double GetFPS() const;
  void Update() override;
  void SetPaused(bool pause);
private:
  double elapsed_time;
  double curr_time;
  double delta_time;
  double fps;
  bool paused;
};

} // namespace UWUEngine