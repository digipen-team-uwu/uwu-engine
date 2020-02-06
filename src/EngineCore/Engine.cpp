#include <UWUEngine/Entity/EntityManager.h>

#include <UWUEngine/Engine.h>
#include <UWUEngine/statemachine.hpp>
#include "GLFW/glfw3.h"
#include <UWUEngine/WindowManager.h>
#include "sstream"
#include <UWUEngine/FrameLimiterSys.h>
#include <UWUEngine/GamePlay/PlayerController.h>

// Systems
SystemUpdater Engine::systemUpdater;

//TextureAtlaser Engine::textureAtlaser;
//TextureLoader Engine::textureLoader;
//Instances Engine::instances;

// Component managers

void Engine::StartUp()
{
	SystemUpdater::StartUp();
	StateMachineUpdater::StartUp();
}

void Engine::Update()
{
	StateMachineUpdater::Update();
	//editor.Update();
	
	SystemUpdater::Update();
    // title
    std::stringstream title;
    title << "Active Entities: " << EntityManager::EntityCount();
    title << " | FPS: " << FrameRateController::GetFPS();
    title << " | Energy: " << PlayerData::GetEnergy();
    glfwSetWindowTitle(WindowManager::getWindowHandle(), title.str().c_str());
}

void Engine::ShutDown()
{
  //textureLoader.ShutDown();

  // delete vbos
  //instances.ShutDown();
}