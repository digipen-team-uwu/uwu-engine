#pragma once
#define GLM_FORCE_SWIZZLE
#include "AllSystems.h"
#include <UWUEngine/Instances.h>

using namespace UWUEngine;

namespace UWUEngine
{
class Engine
{
public:
	//static CompSystem compManager; //deprecated

	//Manager
	//TODO::spine animation manager

    //static TextureAtlaser textureAtlaser;
    //static TextureLoader textureLoader;
    //static Instances instances;

    Engine();
    ~Engine() = default;
	static void StartUp();
	static void Update();
	static void ShutDown();
  typedef Space<System, LogSys, EventSystem, WindowSys, EditorSys, 
    InputSys, ActionSys, EntityCacher, EntitySys, TextureLoader,
    AtlasModule, UISys, DebugManager, SceneSys,
    FrameLimiterSys, TimerSys, CompSpaceSys, RenderSys, CameraSys, 
    DragAndDropSys, ShaderModule, UBOModule, Instances> SystemSpace;
private:
  SystemSpace systems;
};
}