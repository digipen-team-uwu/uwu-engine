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
    void Step();
    using SystemSpace = Space<System,

      LogSys,
      WindowSys,
      RenderSys,
      InputSys,
      FrameLimiterSys,
      EventSys,
      TimerSys,
      SceneSys,
      EntitySys,
      CompSpaceSys,
      CameraSys,
      PhysicsSys,

      //Modules
      SpineDataMod,
      TextureLoaderMod,
      UBOMod,
      SSBOMod
    >;
    SystemSpace& GetSystems() { return systems; }
  private:
    //These are in new lines now because they are our init order now.
    SystemSpace systems;
  };
}