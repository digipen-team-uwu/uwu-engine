/******************************************************************************/
/*!
\par        Project Umbra
\file       FangGrounded.cpp
\author     Yi Qian
\date       2019/12/05
\brief      Fang grounded behavior,I hate file header comments

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#include <UWUEngine/GamePlay/FangBehavior.h>
#include <UWUEngine/Component/SpineAnimationComponentManager.h>
#include <UWUEngine/Component/TransformComponentManager.h>
#include "glm/vec3.hpp"

#define AGGRO_RANGE 2000

void Behavior<EntityManager::Type::Fang_>::Load_Grounded()
{
    // DNI
}

void Behavior<EntityManager::Type::Fang_>::Enter_Grounded()
{
    SpineAnimationComponentManager::GetAnimation(GetID()).ChangeAnimation("Idle", true);
}

void Behavior<EntityManager::Type::Fang_>::Update_Grounded(float dt)
{
  glm::vec2 playerPosition = TransformComponentManager::GetTranslation(PlayerData::GetPlayerID());
  glm::vec2 selfPosition = TransformComponentManager::GetTranslation(GetID());

  float distance = length(playerPosition - selfPosition);

  if (distance < AGGRO_RANGE)
  {
    SetNextState(Running);
  }
}

void Behavior<EntityManager::Type::Fang_>::Exit_Grounded()
{
    // Currently exists to suppress compiler warnings
}

void Behavior<EntityManager::Type::Fang_>::Unload_Grounded()
{
	// DNI
}
