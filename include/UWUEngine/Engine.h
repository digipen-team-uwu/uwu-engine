#pragma once
#define GLM_FORCE_SWIZZLE
#include <UWUEngine/System.h>

class Engine
{
public:
	//Systems
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
