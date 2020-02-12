#include <UWUEngine/Entity/EntitySys.h>
#include <UWUEngine/Space.h>
#include <UWUEngine/Engine.h>
#include <UWUEngine/statemachine.hpp>
#include "GLFW/glfw3.h"
#include <UWUEngine/WindowSys.h>
#include "sstream"
#include <UWUEngine/FrameLimiterSys.h>
#include <UWUEngine/GamePlay/PlayerController.h>
// Systems

//TextureAtlaser Engine::textureAtlaser;
//TextureLoader Engine::textureLoader;
//Instances Engine::instances;



// Component managers
namespace UWUEngine
{

Engine::Engine()
{
  systems = new 
}
void Engine::StartUp()
{
	StateMachineUpdater::StartUp();
}

void Engine::Update()
{
	StateMachineUpdater::Update();
	//editor.Update();
	
	SystemUpdater::Update();
    // title
    std::stringstream title;
    title << "Active Entities: " << EntitySys::EntityCount();
    title << " | FPS: " << FrameRateController::GetFPS();
    title << " | Energy: " << PlayerData::GetEnergy();
    glfwSetWindowTitle(WindowSys::getWindowHandle(), title.str().c_str());
}

void Engine::ShutDown()
{
  //textureLoader.ShutDown();

  // delete vbos
  //instances.ShutDown();
}
}