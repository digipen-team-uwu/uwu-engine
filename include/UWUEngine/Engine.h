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
      CompSpaceSys,
      RenderSys,
      EditorSys,
      InputSys,
      FrameLimiterSys,
      EventSys,
      TimerSys,
      SceneSys,
      EntitySys,
      CameraSys,
      PhysicsSys,
      ColliderSys,
      AnimationSys,
      BehaviorSys,
      SpineAnimationSys,
      LightSys,

      //Modules
      VAOMod,
      SpineDataMod,
      TextureLoaderMod,
      TextureAtlaserMod,
      UBOMod,
      SSBOMod,
      ShaderMod,
      InstancingMod
    >;
    SystemSpace& GetSystems() { return systems; }
  private:
    //These are in new lines now because they are our init order now.
    SystemSpace systems;
  };
}