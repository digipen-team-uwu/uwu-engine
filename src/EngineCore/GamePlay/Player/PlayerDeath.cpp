/******************************************************************************/
/*!
\par        Project Umbra
\file       PlayerDash.cpp
\author     Michael Rollosson Halbhuber
\date       2019/11/18
\brief      Manages the player's dash state

Copyright © 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#include <UWUEngine/GamePlay/PlayerController.h>
#include <UWUEngine/Component/SpineAnimationComponentManager.h>
#include <UWUEngine/Component/TransformComponentManager.h>
#include <UWUEngine/Timer.h>
#include <UWUEngine/GameStatesManager.h>
#include <UWUEngine/Audio/SoundInterface.h>
#include <UWUEngine/Scene/SceneManager.h>

static Timer DeathTimer;
// Don't implement
void PlayerStateMachine::Load_Death()
{
    // Pointless
}

void PlayerStateMachine::Enter_Death()
{
  SoundInterface::playSound("player_dead");

  DeathTimer.SetDuration(2);
  DeathTimer.Start();
  PhysicsComponentManager::SetVelocity({}, PlayerData::GetPlayerID());
    SpineAnimationComponentManager::GetAnimation(PlayerData::GetPlayerID()).ChangeAnimation("death", false);
}

void PlayerStateMachine::Update_Death(float dt)
{
  if (DeathTimer.Finished())
  {
    SceneManager::Reload();
  }
}

void PlayerStateMachine::Exit_Death()
{
}

// Don't implement
void PlayerStateMachine::Unload_Death()
{
    // Pointless
}
