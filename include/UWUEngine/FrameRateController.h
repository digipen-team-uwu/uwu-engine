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
#include <UWUEngine/BaseSystem.h>


class FrameRateController : public BaseSystem<FrameRateController>
{
    public:
        FrameRateController() = default;
        ~FrameRateController() = default;
        template<typename T>
        static T GetDeltaTime()
        {
          if (paused)
          {
            return 0.0f;
          }
          return static_cast<T>((delta_time > .25f) ? 0.016666666667f : delta_time);
        }
        template<typename T>
        static T GetConstantDeltaTime()
        {
          return static_cast<T>((delta_time > .25f) ? 0.016666666667f : delta_time);
        }
        static double GetFPS();
        void Update() override;
        static void SetPaused(bool pause);
    private:
        static double elapsed_time;
        static double curr_time;
        static double delta_time;
        static double fps;
        static bool paused;
};
