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
    Space<System, LogSys, WindowSys> systems;
  };
}