/******************************************************************************/
/*!
\par        Project Umbra
\file       PlayerHurt.cpp
\author     Yi Qian
\date       2019/12/05
\brief      Player hurt behavior,I hate file header comments

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#include <UWUEngine/GamePlay/PlayerController.h>
#include <UWUEngine/Component/PhysicsComponentManager.h>
#include <UWUEngine/Audio/SoundInterface.h>

glm::vec2 HurtDir = {};
glm::vec2 HurtVel;

//Don't implement this
void PlayerStateMachine::Load_Hurt()
{ 
}

void PlayerStateMachine::Enter_Hurt()
{
  SoundInterface::playSound("player_hurt");

  //If HurtDir is not initialized, initialize it
  if (!HurtDir.x && !HurtDir.y)
  {
    HurtDir = {cosf(PlayerData::HurtDir), sinf(PlayerData::HurtDir)};
  }

  PlayerData::HurtTimer.SetDuration(PlayerData::HurtTime);
  PlayerData::HurtTimer.Start();

  HurtVel = HurtDir;
  HurtVel.x = PlayerData::HurtFromRight ? HurtDir.x : -HurtDir.x;
  HurtVel *= PlayerData::HurtSpeed;

  //Set Player hurt velocity
  PhysicsComponentManager::SetVelocity({HurtVel, 0, 0}, PlayerData::GetPlayerID());
}

void PlayerStateMachine::Update_Hurt(float dt)
{
  if (PlayerData::HurtTimer.Running())
  {
    if (PlayerData::HurtTimer.Finished())
    {
      PlayerData::HurtTimer.Stop();
      PhysicsComponentManager::SetVelocity({}, PlayerData::GetPlayerID());
      SetNextState(Airborne);
    }
  }
}

void PlayerStateMachine::Exit_Hurt()
{
  
}

//Don't implement this
void PlayerStateMachine::Unload_Hurt()
{
  
}
