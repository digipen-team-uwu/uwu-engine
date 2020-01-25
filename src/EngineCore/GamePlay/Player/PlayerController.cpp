/******************************************************************************/
/*!
\par        Project Umbra
\file       PlayerController.cpp
\author     Yi Qian
\date       2019/12/05
\brief      Player Behavior,I hate file header comments

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#include <UWUEngine/FrameRateController.h>
#include <UWUEngine/constants.h>
#include <UWUEngine/Component/TransformComponentManager.h>
#include <UWUEngine/GamePlay/PlayerController.h>
#include <UWUEngine/Graphics/Camera.h>
#include <UWUEngine/Input/InputManager.h>
#include <UWUEngine/Debugs/TraceLogger.h>
#include <UWUEngine/Debugs/ColoredOutput.h>
#include <UWUEngine/Serialization.h>

#include <glm/gtc/constants.hpp>

//Player Data
EntityID PlayerData::playerID;
size_t PlayerData::health = 3;
size_t PlayerData::energy = 100;

//Player static Data
bool PlayerData::HurtFromRight;
float PlayerData::HurtSpeed = 3000;
float PlayerData::HurtTime = .25;
//This has to be a value in between [-pi/2, pi/2]
float PlayerData::HurtDir = 0.3;
Timer PlayerData::HurtTimer;

Timer PlayerData::DashCooldown;
PlayerStateMachine::_PlayerStateMachinestate PlayerData::currState = PlayerStateMachine::_PlayerStateMachinestate::Grounded;

glm::vec4 PlayerData::lastSafePos;

//Cheats
bool PlayerData::isInvincible = false;

void PlayerData::InitPlayer()
{
  health = 3;
  energy = 10;
}

void PlayerData::Hurt(size_t damage)
{
  if (isInvincible)
  {
    return;
  }
  health -= damage;

  if (health > 99999)
    health = 0;
}

EntityID PlayerData::GetPlayerID()
{
  return playerID;
}

void PlayerData::LoseEnergy(size_t energy_)
{
  energy -= energy_;
  if (energy > 99999)
    energy = 0;
}

void PlayerData::GainEnergy(size_t energy_)
{
  energy += energy_;
}

size_t PlayerData::GetEnergy()
{
  return energy;
}

size_t PlayerData::GetHealth()
{
  return health;
}



PlayerStateMachine::_PlayerStateMachinestate PlayerData::GetCurrentState()
{
  return currState;
}


Behavior<EntityManager::Type::Player>::Behavior(EntityID id) :BaseBehavior(id)
{
  PlayerData::playerID = GetID();
  PlayerData::InitPlayer();
}

Behavior<EntityManager::Type::Player>::~Behavior() = default;

void Behavior<EntityManager::Type::Player>::Update()
{
  player_state_.UpdateState(FrameRateController::GetDeltaTime<float>());

  if (PlayerData::GetHealth() == 0)
    player_state_.SetNextState(PlayerStateMachine::Death);

  if (
  (InputManager::KeyHeld(GLFW_KEY_LEFT_CONTROL)||InputManager::KeyHeld(GLFW_KEY_RIGHT_CONTROL)) && 
  InputManager::KeyPressed('Z'))
  {
    if (PlayerData::isInvincible)
    {
      TraceLogger::Log(TraceLogger::INFO) << "Invincibility: " << Set(Red) << "OFF" << Set() << std::endl;
    }
    else
    {
      TraceLogger::Log(TraceLogger::INFO) << "Invincibility: " << Set(Green) << "ON" << Set() << std::endl;
    }

    PlayerData::isInvincible = !PlayerData::isInvincible;
  }

  //Camera::SetCameraTarget(TransformComponentManager::GetTranslation(PlayerData::GetPlayerID()));
  //Camera::SetCameraPosition(glm::vec3(glm::vec2(TransformComponentManager::GetTranslation(PlayerData::GetPlayerID())) + glm::vec2{0, 100}, Camera::GetCameraPosition().z));
}

void Behavior<EntityManager::Type::Player>::Serialize(std::ofstream & stream)
{
  stream << ",\n";
  stream << Tabs::TWO;
  stream << "\"behavior\": true";
}

void Behavior<EntityManager::Type::Player>::Deserialize(rapidjson::Value & object, EntityID ID, const char* filePath)
{
}

void Behavior<EntityManager::Type::Player>::OnCollide(CollisionInfo const& info)
{
  // First check and see if the thing was a hazard
  EntityID collidingWith = GetID() == info.obj1 ? info.obj2 : info.obj1;

  // Separate states
  switch (player_state_.GetCurrentState())
  {
  case PlayerStateMachine::Grounded:
    OnCollideGrounded(info);
    break;
  case PlayerStateMachine::Airborne:
    OnCollideAirborne(info);
    break;
  case PlayerStateMachine::Dash:
    OnCollideDash(info);
    break;
  default:;
  }
}

glm::vec2 Behavior<EntityManager::Type::Player>::CalculateResolveAngle(CollisionInfo const& info) const
{
  EntityID collidingWith = GetID() == info.obj1 ? info.obj2 : info.obj1;

  glm::vec2 trans1 = TransformComponentManager::GetTranslation(GetID());
  glm::vec2 trans2 = TransformComponentManager::GetTranslation(collidingWith);
  bool positive = glm::dot(trans1, info.direction) > glm::dot(trans2, info.direction);

  //Not sure if it needs to be normalized or not, normalized it just in case
  return positive ? info.direction : -info.direction;
}

Behavior<EntityManager::Type::Player>::ABSTRACT_DIR Behavior<EntityManager::Type::Player>::GetAbstractDirection(float angle) const
{
  constexpr float piOverFour = glm::pi<float>() / 4;
  if (angle < piOverFour && angle >= -piOverFour)
  {
    return ABSTRACT_DIR::RIGHT;
  }
  if (angle < -piOverFour && angle >= -3 * piOverFour)
  {
    return ABSTRACT_DIR::BOTTOM;
  }
  if (angle >= piOverFour && angle < 3 * piOverFour)
  {
    return ABSTRACT_DIR::TOP;
  }
  if (angle < -3 * piOverFour || angle >= 3 * piOverFour)
  {
    return ABSTRACT_DIR::LEFT;
  }
  return ABSTRACT_DIR::INVALID;
}

bool Behavior<EntityManager::Type::Player>::IsDirectionRight(float angle) const
{
  constexpr float piOverTwo = glm::pi<float>() / 2;
  if (angle > -piOverTwo && angle < piOverTwo)
  {
    return true;
  }
  return false;
}

// Below code written by Michael Rollosson Halbhuber

bool PlayerData::FacingRight()
{
  return (TransformComponentManager::GetScale(playerID).x > 0);
}

void PlayerData::SetLastSafePos(glm::vec4 pos)
{
  lastSafePos = pos;
}

glm::vec4 const& PlayerData::GetLastSafePos()
{
  return lastSafePos;
}

void PlayerData::ResetPlayerPos()
{
  TransformComponentManager::SetTranslation(GetLastSafePos(), GetPlayerID());
}
