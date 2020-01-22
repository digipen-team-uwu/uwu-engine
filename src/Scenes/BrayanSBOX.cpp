﻿/******************************************************************************/
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
#include <UWUEngine/Engine.h>
#include <UWUEngine/Component/LightingComponentManager.h>
#include <UWUEngine/Behaviors/DynamicCamera.h>
#include <UWUEngine/Audio/SoundInterface.h>
#include <UWUEngine/Graphics/Camera.h>
#include <UWUEngine/Graphics/Debugs/Picker.h>
#include <UWUEngine/Editor/Windows/EditorEntityViewer.h>

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

  DynamicCamera::Activate();
  Lighting::Activate();
  TextureAtlaser::LoadAtlasPage();

  SoundInterface::playSound("music_calm1", true);
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
#ifndef _DEBUG
  DynamicCamera::SetTrackingPos(glm::vec4(glm::vec2(TransformComponentManager::GetTranslation(PlayerData::GetPlayerID())) + glm::vec2{ 0, 100 }, Camera::GetCameraPosition().z, 1));
  DynamicCamera::SetTrackingSpeed(2);
  DynamicCamera::SetInnerBounds(100, 100, { 0, 100 });
#else
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
#endif

  if (InputManager::MousePressed(InputConstants::Mouse::LEFT_CLICK))
  {
    Picker p = Picker();
    EntityID ID = p.Pick();
    Editors::EntityViewer::SetSelectedEntity(ID);
  }
}

void GameStateMachine::Exit_BrayanSBOX()
{
  SoundInterface::stopAllSounds();
  EntityManager::DestroyAll();
  TextureAtlaser::ClearData();

  #ifdef _DEBUG_
  Editor::Stop();
#endif
}