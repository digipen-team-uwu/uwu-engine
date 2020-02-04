/******************************************************************************/
/*!
\par        Project Umbra
\file       PlayerGrounded.cpp
\author     Yi Qian
\date       2019/12/05
\brief      Player grounded behavior,I hate file header comments

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#include <UWUEngine/GamePlay/PlayerController.h>
#include <UWUEngine/Input/InputManager.h>
#include <UWUEngine/Component/SpineAnimationComponentManager.h>
#include <UWUEngine/Component/TransformComponentManager.h>
#include <UWUEngine/Input/ActionManager.h>
#include <UWUEngine/GameStatesManager.h>
#include <UWUEngine/Audio/SoundInterface.h>

void PlayerStateMachine::Load_Grounded()
{
}

void PlayerStateMachine::Enter_Grounded()
{
	SpineAnimationComponentManager::GetAnimation(PlayerData::GetPlayerID()).ChangeAnimation("idle", true);
  
    // Start the dash cooldown
    if (!PlayerData::DashCooldown.Running())
    {
        PlayerData::DashCooldown.Start();
    }
  if (ActionManager::GetActionHeld(ActionManager::Run)/*InputManager::KeyHeld('d') || InputManager::KeyHeld('a')*/)
  {
    SpineAnimationComponentManager::GetAnimation(PlayerData::GetPlayerID()).ChangeAnimation("run", true);
  }

    PlayerData::currState = Grounded;
}

void PlayerStateMachine::Update_Grounded(float dt)
{
  //Default to falling state
  SetNextState(Airborne);

	EntityID sight = PlayerData::GetPlayerID();
	
	glm::vec4 gravity = { 0, -800.f, 0, 0 };
	glm::vec4 movement = {};

  movement.x += 1000.f * (ActionManager::GetActionHeld(ActionManager::Right) - ActionManager::GetActionHeld(ActionManager::Left)); //(!!InputManager::KeyHeld('d') - !!InputManager::KeyHeld('a'));

	static bool walking_anim = false;

	if (movement.x != 0 && walking_anim == false)
	{
		walking_anim = true;
    SoundInterface::playSound("player_step", true);
		SpineAnimationComponentManager::GetAnimation(sight).ChangeAnimation("run", true);
	}
	else if (movement.x == 0 && walking_anim == true)
	{
		SpineAnimationComponentManager::GetAnimation(sight).ChangeAnimation("idle", true);
    SoundInterface::stopSound("player_step");
		walking_anim = false;
	}
	glm::vec4 vel = PhysicsComponentManager::GetVelocity(sight);

    // Set this point to the last safe position
    if (abs(vel.x) <= 5 && abs(vel.y) <= 5)
    {
        PlayerData::SetLastSafePos(TransformComponentManager::GetTranslation(sight));
    }

	if (ActionManager::GetActionPressed(ActionManager::Jump))//InputManager::KeyPressed('w'))
	{
		vel.y = 650.f;
		glm::vec4 translation = TransformComponentManager::GetTranslation(sight);
		translation.y += 5;
		TransformComponentManager::SetTranslation(translation, sight);
		SetNextState(Airborne);
		SoundInterface::playSound("player_jump");
	}

    if (ActionManager::GetActionPressed(ActionManager::Dash))//InputManager::KeyPressed(' '))
    {
        if (PlayerData::DashCooldown.Finished())
        {
          walking_anim = false;
            SetNextState(Dash);
        }
    }

	static float direction = 1;
	if (glm::sign(movement.x))
		direction = glm::sign(movement.x);

	TransformComponentManager::SetScale({ direction * 200.f, 200.f, 1 }, sight);

	PhysicsComponentManager::SetVelocity(vel, sight);

	PhysicsComponentManager::SetDrag({ 2.f, 0.f, 0.f, 0.f }, sight);

	PhysicsComponentManager::SetAcceleration(movement + gravity, sight);
  //PhysicsComponentManager::SetAcceleration(movement, sight);

    

}

void PlayerStateMachine::Exit_Grounded()
{
}

void PlayerStateMachine::Unload_Grounded()
{
}

void Behavior<EntityManager::Type::Player>::OnCollideGrounded(const Event<EventType::Collision>& info)
{
  glm::vec2 resolveAngle = CalculateResolveAngle(info);
  float angle = atan2(resolveAngle.y, resolveAngle.x);

  EntityID collidingWith = GetID() == info.obj1 ? info.obj2 : info.obj1;

  switch (EntityManager::GetType(collidingWith))
  {
  case Type::Solid:
    //Fix state to grounded
    if (player_state_.GetNextState() == PlayerStateMachine::Airborne)
    {
      player_state_.SetNextState(PlayerStateMachine::Grounded);
    }
    break;
  case Type::Fang_:
    //Get hurt and knock back
    PlayerData::Hurt(1);
    PlayerData::HurtFromRight = IsDirectionRight(angle);
    player_state_.SetNextState(PlayerStateMachine::Hurt);

    break;
  case Type::Perception:
    //Get hurt and knock back
    PlayerData::Hurt(1);
    PlayerData::HurtFromRight = IsDirectionRight(angle);
    player_state_.SetNextState(PlayerStateMachine::Hurt);

    break;
  case Type::Hazard:
    PlayerData::Hurt(1);
    PlayerData::ResetPlayerPos();

    break;
  case Type::LevelEnd:
    for (auto i : StateMachineUpdater::GetMachines())
    {
      GameStateMachine* gameStateMachine = dynamic_cast<GameStateMachine*>(i);
      if (gameStateMachine)
      {
        gameStateMachine->SetNextState(GameStateMachine::End);
      }
    }

    break;

  default: ;
  }
}
