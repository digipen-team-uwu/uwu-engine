/******************************************************************************/
/*!
\par        Project Umbra
\file       PlayerAirborne.cpp
\author     Yi Qian
\date       2019/12/05
\brief      Player airborne behavior,I hate file header comments

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#include <UWUEngine/GamePlay/PlayerController.h>
#include <UWUEngine/Input/InputManager.h>
#include <UWUEngine/Component/TransformComponentManager.h>
#include <UWUEngine/Component/SpineAnimationComponentManager.h>
#include <UWUEngine/Input/ActionManager.h>
#include <UWUEngine/GameStatesManager.h>
#include <UWUEngine/Audio/SoundInterface.h>

//Don't implement
void PlayerStateMachine::Load_Airborne()
{
}

void PlayerStateMachine::Enter_Airborne()
{
	//std::cout << "Entering Airborne state" << std::endl;
    PlayerData::currState = Airborne;
    SpineAnimationComponentManager::GetAnimation(PlayerData::GetPlayerID()).ChangeAnimation("jumpLaunch", false);

}

void PlayerStateMachine::Update_Airborne(float dt)
{
	EntityID sight = PlayerData::GetPlayerID();

	glm::vec4 gravity = { 0, -800.f, 0, 0 };
	glm::vec4 movement = {};

  movement.x += 1000.f * (ActionManager::GetActionHeld(ActionManager::Right) - ActionManager::GetActionHeld(ActionManager::Left));//(!!InputManager::KeyHeld('d') - !!InputManager::KeyHeld('a'));

    if (ActionManager::GetActionPressed(ActionManager::Dash))//InputManager::KeyPressed(' '))
    {
        if (PlayerData::DashCooldown.Running() && PlayerData::DashCooldown.Finished())
        {
            SetNextState(Dash);
        }
    }

	static float direction = 1;
	if (glm::sign(movement.x))
		direction = glm::sign(movement.x);

	TransformComponentManager::SetScale({ direction * 200.f, 200.f, 1 }, sight);

	PhysicsComponentManager::SetDrag({ 2.f, 0.f, 0.f, 0.f }, sight);

	PhysicsComponentManager::SetAcceleration(movement + gravity, sight);
}

void PlayerStateMachine::Exit_Airborne()
{
	
}

// Don't implement
void PlayerStateMachine::Unload_Airborne()
{
}

void Behavior<EntityManager::Type::Player>::OnCollideAirborne(const Event<EventType::Collision>& info)
{
  // Calculate the resolution angle
  glm::vec2 resolveAngle = CalculateResolveAngle(info);
  float angle = atan2(resolveAngle.y, resolveAngle.x);

  const EntityID collidingWith = GetID() == info.obj1 ? info.obj2 : info.obj1;

  // Branch according to object type
  switch (EntityManager::GetType(collidingWith))
  {
  case Type::Solid:
    // Land
    if (GetAbstractDirection(angle)==ABSTRACT_DIR::TOP)
    {
      SpineAnimationComponentManager::GetAnimation(GetID()).ChangeAnimation("jumpLand", false);
      SoundInterface::playSound("player_land");
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
