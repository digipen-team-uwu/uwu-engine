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

// Magnitude of the dash acceleration stage
#define DASH_MAGNITUDE 8000.0f

//magnitude of the upwards burst at end of dash
#define DASH_END_MAGNITUDE 4000.0f

// Total drag during the end dash
#define X_DRAG_MAGNITUDE 5.0f
#define Y_DRAG_MAGNITUDE 5.0f

// Hard angle for testing
#define TEST_ANGLE glm::radians(0.0f)

// The full length of the dash
#define DASH_TIME 0.4f

#define DASH_COOLDOWN 1.0f

// Time defines for the timers

#define ACCEL_TIME 0.15f
#define DRAG_TIME  0.05f
#define END_TIME  0.2f
#define MAIN_TIME  DASH_TIME - ACCEL_TIME - DRAG_TIME - END_TIME

static Timer DashAccelTimer; // Tracks the amount of time the opening burst of acceleration lasts for
static Timer DashMainTimer;  // Tracks the amount of time the main body of the dash lasts for
static Timer DashDragTimer;  // Tracks the amount of time the end drag of the dash lasts for
static Timer DashEndTimer;

static float angle;

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
    DashAccelTimer.SetDuration(ACCEL_TIME);
    DashMainTimer.SetDuration(MAIN_TIME);
    DashDragTimer.SetDuration(DRAG_TIME);
    DashEndTimer.SetDuration(END_TIME);

    // Start the accel timer (stage one)
    DashAccelTimer.Start();

    // Set the angle (Just a test angle for now)
    angle = TEST_ANGLE;

    PlayerData::currState = Dash;
}

void PlayerStateMachine::Update_Dash(float dt)
{
    // Check if the accel timer has finished
    if (DashAccelTimer.Running())
    {
        // Check if the accel timer has finished
        if (!DashAccelTimer.Finished())
        {
            // Get a unit vector based on an angle
          glm::vec4 accel = VectorFromAngle(ActionManager::GetDashAngle());//angle);

            // Multiply the magnitude of the vector
            accel.x *= DASH_MAGNITUDE;
            accel.y *= DASH_MAGNITUDE;

            // Check if the player is facing left
            //if (!PlayerData::FacingRight())
            //{
            //    // Invert the x acceleration
            //    accel.x *= -1.0f;
            //}

            // Set the acceleration of the player
            PhysicsComponentManager::SetAcceleration(accel, PlayerData::playerID);
        }
        else
        {
            // Stop the accel timer
            DashAccelTimer.Stop();

            // Start the main timer
            DashMainTimer.Start();
        }
    }
    
    // Check if the main timer is running
    if (DashMainTimer.Running())
    {
        // Check if the main timer has finished
        if (!DashMainTimer.Finished())
        {
            // Right now, does nothing, but it might in the future maybe depending
        }
        else
        {
            // Stop the main timer
            DashMainTimer.Stop();

            // Start the drag timer
            DashDragTimer.Start();
        }
    }

    // Check if the drag timer is running
    if (DashDragTimer.Running())
    {
        // Check if the drag timer is finished
        if (!DashDragTimer.Finished())
        {
            // Get a unit vector based on an angle (just a test angle right now)
            glm::vec4 drag = { 0, 0, 0, 0 };

            drag.x = X_DRAG_MAGNITUDE;
            drag.y = Y_DRAG_MAGNITUDE;

            // Set the acceleration of the player
            PhysicsComponentManager::SetDrag(drag, PlayerData::playerID);
        }
        else
        {
          // Stop the accel timer
          DashDragTimer.Stop();

          // Start the main timer
          DashEndTimer.Start();
        }
    }

    if (DashEndTimer.Running())
    {
      // Check if the accel timer has finished
      if (!DashEndTimer.Finished())
      {
        // Set the acceleration of the player
        PhysicsComponentManager::SetAcceleration({ 0, DASH_END_MAGNITUDE, 0, 0 }, PlayerData::playerID);
      }
      else
      {
        PlayerData::DashCooldown.Stop();

        // Exit the dash
        SetNextState(Airborne);
      }
    }


	//TODO: redo this later
    //if (ColliderComponentManager::IsColliding(PlayerData::GetPlayerID(), EntityManager::Solid))
    //{
    //    SetNextState(Airborne);
    //}

	
}

void PlayerStateMachine::Exit_Dash()
{
    DashAccelTimer.Stop();
    DashMainTimer.Stop();
    DashDragTimer.Stop();
    DashEndTimer.Stop();

    // Set the Dash cooldown and stop it
    PlayerData::DashCooldown.SetDuration(DASH_COOLDOWN);
    PlayerData::DashCooldown.Stop();
}

// Don't implement
void PlayerStateMachine::Unload_Dash()
{
    // Pointless
}

void Behavior<EntityManager::Type::Player>::OnCollideDash(CollisionInfo const& info)
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
