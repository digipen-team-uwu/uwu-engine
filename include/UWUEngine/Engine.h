#pragma once
#define GLM_FORCE_SWIZZLE
#include <UWUEngine/BaseSystem.h>
#include <UWUEngine/Timer.h>
#include <UWUEngine/Graphics/Texture/TextureLoader.h>
#include <UWUEngine/Graphics/Texture/TextureAtlaser.h>
#include <UWUEngine/Instances.h>

class Engine
{
public:
	//Systems
	static TimerManager timerManager;
	static SystemUpdater systemUpdater;

	//static CompSystem compManager; //deprecated

	//Manager
	//TODO::spine animation manager

    //static TextureAtlaser textureAtlaser;
    //static TextureLoader textureLoader;
    //static Instances instances;

    Engine() = default;
    ~Engine() = default;
	static void StartUp();
	static void Update();
	static void ShutDown();

};
