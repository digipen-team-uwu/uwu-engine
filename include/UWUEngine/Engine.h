#pragma once

#include <UWUEngine/Space.h>
#include <UWUEngine/Systems/AllSystems.h>

namespace UWUEngine
{
  class Engine
  {
  public:
    Engine() = default;
    ~Engine() = default;
    void Run();
  private:
    //These are in new lines now because they are our init order now.
    Space<
    System,
    LogSys,
    WindowSys,
    FrameLimiterSys,
    EventSys
    > systems;
  };
}