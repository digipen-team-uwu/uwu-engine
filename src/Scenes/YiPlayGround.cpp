/******************************************************************************/
/*!
\par        Project Umbra
\file       YiPlayGround.cpp
\author     Yi Qian
\date       2019/12/05
\brief      Yi's test scene,I hate file header comments

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#include <UWUEngine/Entity/EntityFactory.h>
#include <UWUEngine/GameStatesManager.h>
#include <UWUEngine/Input/InputManager.h>
#include <UWUEngine/Serialization.h>
#include <UWUEngine/Graphics/Texture/TextureAtlaser.h>

static std::vector<EntityID> objects;

void GameStateMachine::Load_YiPlayGround()
{
  objects = DeserializeLevel("BrayanSBOX");
  TextureAtlaser::LoadAtlasPage();
  Editor::Start();
}

void GameStateMachine::Enter_YiPlayGround()
{

}

void GameStateMachine::Update_YiPlayGround(float dt)
{
	//Scene Switching
	if (InputManager::KeyPressed('1'))
	{
		SetNextState(Level1);
	}
	if (InputManager::KeyPressed('2'))
	{
		SetNextState(Level2);
	}
	if (InputManager::KeyPressed('3'))
	{
		SetNextState(Restart);
	}

	if (InputManager::KeyPressed('4'))
	{
		SetNextState(BrayanSBOX);
	}
}

void GameStateMachine::Exit_YiPlayGround()
{
	EntityManager::DestroyAll();
}

void GameStateMachine::Unload_YiPlayGround()
{

}
