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
#include <UWUEngine/Input/InputManager.h>
#include <UWUEngine/Component/SpineAnimationComponentManager.h>
#include <UWUEngine/Component/TransformComponentManager.h>
#include <UWUEngine/Timer.h>
#include <UWUEngine/Helper.h>
#include <UWUEngine/Input/ActionManager.h>
#include <glm/glm.hpp>
#include <UWUEngine/GameStatesManager.h>
#include <UWUEngine/Audio/SoundInterface.h>
#include <glm/gtc/constants.hpp>

// Pi Defines for Angle Returns - Michael
#define PI                 (glm::pi<float>())
#define RAD_UP             (PI / 2.0f)
#define RAD_RIGHT          0
#define RAD_LEFT           PI
#define RAD_DOWN           ((-1.0f * PI) / 2.0f)
#define RAD_UPRIGHT        (PI / 4.0f)
#define RAD_UPLEFT         ((3.0f * PI) / 4.0f)
#define RAD_DOWNRIGHT      ((-1.0f * PI) / 4.0f)
#define RAD_DOWNLEFT       ((-3.0f * PI) / 4.0f)
#define THIRTY_DEG_IN_RAD  (PI / 6.0f)
#define FIFTEEN_DEG_IN_RAD (PI / 12.0f)

// Magnitude of the dash acceleration stage
#define DASH_MAGNITUDE 1500.0f

// The full length of the dash
#define DASH_TIME 0.2f

#define DASH_COOLDOWN 0.005f

// Exit velocity of the dash
#define X_DRIFT_MULT 0.25f
#define Y_DRIFT_MULT 0.55f


static Timer DashTimer;  // Tracks the amount of time the main body of the dash lasts for


// Don't implement
void PlayerStateMachine::Load_Dash()
{
    // Pointless
}

void PlayerStateMachine::Enter_Dash()
{
  SoundInterface::playSound("player_dash");

    // Enter the dash animation
    SpineAnimationComponentManager::GetAnimation(PlayerData::GetPlayerID()).ChangeAnimation("dash", false);

    // Set the timer durations
    DashTimer.SetDuration(DASH_TIME);
    DashTimer.Start();

    // Get the angle
    float angle = ActionManager::GetDashAngle();

    // Hard adjust the angle towards one of the eight directions
    // Non-cardinal directions take precedence and have a wider range to make the controls feel better
    if (angle <= RAD_UPRIGHT + THIRTY_DEG_IN_RAD && angle >= RAD_UPRIGHT - THIRTY_DEG_IN_RAD)
    {
        angle = RAD_UPRIGHT;
    }
    else if (angle <= RAD_UPLEFT + THIRTY_DEG_IN_RAD && angle >= RAD_UPLEFT - THIRTY_DEG_IN_RAD)
    {
        angle = RAD_UPLEFT;
    }
    else if (angle <= RAD_DOWNLEFT + THIRTY_DEG_IN_RAD && angle >= RAD_DOWNLEFT - THIRTY_DEG_IN_RAD)
    {
        angle = RAD_DOWNLEFT;
    }
    else if (angle <= RAD_DOWNRIGHT + THIRTY_DEG_IN_RAD && angle >= RAD_DOWNRIGHT - THIRTY_DEG_IN_RAD)
    {
        angle = RAD_DOWNRIGHT;
    }
    else if (angle <= RAD_RIGHT + FIFTEEN_DEG_IN_RAD && angle >= RAD_RIGHT - FIFTEEN_DEG_IN_RAD)
    {
        angle = RAD_RIGHT;
    }
    else if (angle <= RAD_UP + FIFTEEN_DEG_IN_RAD && angle >= RAD_UP - FIFTEEN_DEG_IN_RAD)
    {
        angle = RAD_UP;
    }
    else if (angle <= RAD_LEFT + FIFTEEN_DEG_IN_RAD && angle >= RAD_LEFT - FIFTEEN_DEG_IN_RAD
            || angle <= (-1.0f * RAD_LEFT + FIFTEEN_DEG_IN_RAD) && angle >= (-1.0f * RAD_LEFT - FIFTEEN_DEG_IN_RAD))
    {
        angle = RAD_LEFT;
    }
    else
    {
        angle = RAD_DOWN;
    }

    glm::vec4 veloc = VectorFromAngle(angle);
    veloc.x *= DASH_MAGNITUDE;
    veloc.y *= DASH_MAGNITUDE;

    PhysicsComponentManager::SetVelocity(veloc, PlayerData::playerID);

    glm::vec4 zero = { 0.0f, 0.0f, 0.0f, 0.0f };
    PhysicsComponentManager::SetDrag(zero, PlayerData::playerID);
    PhysicsComponentManager::SetAcceleration(zero, PlayerData::playerID);

    PlayerData::currState = Dash;

    
}

void PlayerStateMachine::Update_Dash(float dt)
{

    if (DashTimer.Finished())
    {
        PlayerData::DashCooldown.Stop();

        // Exit the dash
        SetNextState(Airborne);
    }
}

void PlayerStateMachine::Exit_Dash()
{
    DashTimer.Stop();

    // Set the Dash cooldown and stop it
    PlayerData::DashCooldown.SetDuration(DASH_COOLDOWN);
    PlayerData::DashCooldown.Stop();

    glm::vec4 veloc = PhysicsComponentManager::GetVelocity(PlayerData::playerID);

    veloc.y *= Y_DRIFT_MULT;
    veloc.x *= X_DRIFT_MULT;

    veloc.x += PlayerData::GetTopXSpeed() * (ActionManager::GetActionHeld(ActionManager::Right) - ActionManager::GetActionHeld(ActionManager::Left));

    PhysicsComponentManager::SetVelocity(veloc, PlayerData::playerID);
}

// Don't implement
void PlayerStateMachine::Unload_Dash()
{
    // Pointless
}

void Behavior<EntityManager::Type::Player>::OnCollideDash(const Event<EventType::Collision>& info)
{
  glm::vec2 resolveAngle = CalculateResolveAngle(info);
  EntityID collidingWith = GetID() == info.obj1 ? info.obj2 : info.obj1;

  switch (EntityManager::GetType(collidingWith))
  {
  case Type::Solid:
    //Become grounded

    break;
  case Type::Fang_:
    //Hurt Enemy and knock back
    player_state_.SetNextState(PlayerStateMachine::Hurt);
    PlayerData::DashCooldown.SetDuration(0);
    PlayerData::DashCooldown.Start();

    break;
  case Type::Perception:
    //Hurt Enemy and knock back
    player_state_.SetNextState(PlayerStateMachine::Hurt);
    PlayerData::DashCooldown.SetDuration(0);
    PlayerData::DashCooldown.Start();

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
        break;
      }
    }

    break;
  default:;
  }
}
