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

      // Systems
      LogSys,
      WindowSys,
      EditorSys,
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
      ColliderSys,
      AnimationSys,
      SpineAnimationSys,
      LightSys,

      //Modules
      VAOMod,
      SpineDataMod,
      TextureLoaderMod,
      UBOMod,
      SSBOMod,
      ShaderMod
    >;
    SystemSpace& GetSystems() { return systems; }
  private:
    //These are in new lines now because they are our init order now.
    SystemSpace systems;
  };
}