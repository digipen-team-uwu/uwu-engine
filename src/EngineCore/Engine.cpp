#include <UWUEngine/Engine.h>

using UWUEngine::Engine;

void Engine::Run()
{
  while (!systems.Get<WindowSys>().shouldClose())
  {
    Step();
  }
}

void Engine::Step()
{
  for (auto s : systems)
  {
    s.second->Update();
  }
}