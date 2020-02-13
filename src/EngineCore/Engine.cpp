#include <UWUEngine/Engine.h>

using UWUEngine::Engine;

void Engine::Run()
{
  while (!systems.Get<WindowSys>().shouldClose())
  {
    for (auto s : systems)
    {
      s.second->Update();
    }
  }
}