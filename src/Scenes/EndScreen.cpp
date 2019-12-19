/******************************************************************************/
/*!
\par        Project Umbra
\file       EndScreen.cpp
\author     Yi Qian
\date       2019/12/05
\brief      End screen scene,I hate file header comments

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#include <UWUEngine/GameStatesManager.h>
#include <UWUEngine/Input/ActionManager.h>
#include <UWUEngine/Graphics/Camera.h>
#include <UWUEngine/Behaviors/DynamicCamera.h>
#include <UWUEngine/Editor.h>
#include <UWUEngine/Serialization.h>
#include <UWUEngine/Graphics/Texture/TextureAtlaser.h>
#include <UWUEngine/Component/LightingComponentManager.h>

void GameStateMachine::Enter_End()
{
  DeserializeLevel("GameEnd");
  DynamicCamera::Deactivate();
  Lighting::Deactivate();

  Camera::ResetCameraPosition();
  auto& ids = EntityManager::GetIDs();
  for (int i = 0; i < ids.size(); ++i)
  {
    LightingComponentManager::SetAmbient(i, glm::vec3(0.1f, 0.1f, 0.2f));
    LightingComponentManager::SetDiffuse(i, glm::vec3(0.5f, 0.5f, 0.5f));
    LightingComponentManager::SetSpecular(i, glm::vec3(1.0f, 1.0f, 1.0f));
    LightingComponentManager::SetShininess(i, 32.f);
  }

  TextureAtlaser::LoadAtlasPage();

#ifdef _DEBUG
  Editor::Start();
#endif
}

void GameStateMachine::Load_End()
{
}

void GameStateMachine::Unload_End() {}

void GameStateMachine::Update_End(float dt)
{
  if (ActionManager::GetActionPressed(ActionManager::Action::Jump))
    SetNextState(BrayanSBOX);
}

void GameStateMachine::Exit_End()
{
  EntityManager::DestroyAll();
  TextureAtlaser::ClearData();

#ifdef _DEBUG
  Editor::Stop();
#endif
}