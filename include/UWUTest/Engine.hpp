#pragma once

#include <UWUEngine/System.h>
#include <UWUEngine/Space.h>

namespace UWUTest
{

template<class ... System>
class Engine
{
  static_assert(sizeof...(System) > 0, "Test engine must have systems in it.");
  //static_assert((std::is_base_of_v<UWUEngine::System, System> && ...), "All classes in a test engine must be systems.");
  using SystemSpace = UWUEngine::Space<UWUEngine::System, System...>;

  SystemSpace systems;
public:
  void Step()
  {
    for (auto s : systems)
    {
      s.second->Update();
    }
  }
  SystemSpace& GetSystems() { return systems; }
};

}