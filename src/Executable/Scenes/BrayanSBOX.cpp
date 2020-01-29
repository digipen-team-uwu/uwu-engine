/******************************************************************************/
/*!
\par        Project Umbra
\file       BrayanSBOX.cpp
\author     Brayan Lopez
\date       2019/10/26
\brief      Brayan's sandbox for testing things out

Copyright � 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#include <UWUEngine/Serialization.h>
#include <UWUEngine/Input/InputManager.h>
#include <UWUEngine/GameStatesManager.h>
#include <UWUEngine/Entity/EntityManager.h>
#include <UWUEngine/Component/TransformComponentManager.h>
#include <UWUEngine/Component/LightingComponentManager.h>
#include <UWUEngine/Behaviors/DynamicCamera.h>
#include <UWUEngine/Audio/SoundInterface.h>
#include <UWUEngine/Graphics/Camera.h>
#include "UWUEngine/Graphics/Texture/TextureAtlaser.h"

static EntityID sight;
static std::vector<EntityID> objects;

void GameStateMachine::Load_BrayanSBOX()
{
}


void GameStateMachine::Enter_BrayanSBOX()
{
  objects = DeserializeLevel("BrayanSBOX");

  for (auto& i : EntityManager::GetIDs())
  {
    if (EntityManager::GetType(i) != Type::Dropped)
    {
      LightingComponentManager::SetShininess(i, 16.0f);
    }
  }

  for (auto i = objects.begin(); i != objects.end(); ++i)
  {
    if (EntityManager::GetType(*i) == EntityManager::Player)
    {
      sight = *i;
    }
  }

  #ifdef _Editor
  DynamicCamera::Deactivate();
  Lighting::Deactivate();
  #else
  DynamicCamera::Activate();
  Lighting::Activate();
  SoundInterface::playSound("music_calm1", true);
  #endif
  TextureAtlaser::LoadAtlasPage();
}

void GameStateMachine::Unload_BrayanSBOX()
{

}

void GameStateMachine::Update_BrayanSBOX(float dt)
{
  for (auto& i : EntityManager::GetIDs())
  {
    if (EntityManager::GetType(i) != Type::Dropped)
    {
      LightingComponentManager::SetShininess(i, 16.0f);
    }
  }
#ifdef _Editor
  static bool dynamic = false;
  if (
    (InputManager::KeyHeld(GLFW_KEY_LEFT_CONTROL) || InputManager::KeyHeld(GLFW_KEY_RIGHT_CONTROL)) &&
    InputManager::KeyPressed('C'))
  {
    dynamic = !dynamic;
  }
  if (dynamic)
  {
    Camera::ResetCameraZoom();
    DynamicCamera::Activate();
    DynamicCamera::SetTrackingPos(glm::vec4(glm::vec2(TransformComponentManager::GetTranslation(PlayerData::GetPlayerID())) + glm::vec2{ 0, 100 }, Camera::GetCameraPosition().z, 1));
    DynamicCamera::SetTrackingSpeed(2);
    DynamicCamera::SetInnerBounds(100, 100, { 0, 100 });
  }
  else
  {
    DynamicCamera::Deactivate();
  }

#else
  DynamicCamera::SetTrackingPos(glm::vec4(glm::vec2(TransformComponentManager::GetTranslation(PlayerData::GetPlayerID())) + glm::vec2{ 0, 100 }, Camera::GetCameraPosition().z, 1));
  DynamicCamera::SetTrackingSpeed(2);
  DynamicCamera::SetInnerBounds(100, 100, { 0, 100 });
#endif

  //if (InputManager::KeyPressed('v'))
  //{
  //	SerializeLevel("BrayanSBOX");
  //}

 // if (InputManager::KeyPressed('c'))
  //{
 //   Camera::ResetCameraPosition();
  //}
 // 
  //if (InputManager::KeyPressed('`'))
  //{
 //   SetNextState(Restart);
  //	DeserializeLevel("BrayanSBOX");
  //}

  //if (InputManager::KeyPressed('2'))
  //{
   // SetNextState(Level2);
 // }

 // if (InputManager::KeyPressed('3'))
 // {
 //   SetNextState(YiPlayGround);
 // }
 // if (InputManager::KeyPressed('1'))
 // {
 //   SetNextState(Level1);
 // }
  /*if (InputManager::KeyPressed('1'))
  {
    SetNextState(End);
  }*/
}

void GameStateMachine::Exit_BrayanSBOX()
{
  SoundInterface::stopAllSounds();
  EntityManager::DestroyAll();
  TextureAtlaser::ClearData();
}