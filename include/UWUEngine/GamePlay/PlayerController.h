/******************************************************************************/
/*!
\par        Project Umbra
\file       PlayerController.h
\author     Yi Qian
\date       2019/12/05
\brief      Player Behavior,I hate file header comments

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#pragma once

#include <UWUEngine/Component/BehaviorComponentManager.h>
#include <UWUEngine/statemachine.hpp>
#include <UWUEngine/Timer.h>

#include <UWUEngine/Physics/Colliders/Collider.h>
#include <UWUEngine/Event/Type/Collision.h>

StateMachine(Player, false, StartUp, Grounded, Airborne, Dash, Hurt, Death)

class PlayerData
{
public:
  static void InitPlayer();

  //Player Helpers
  static void Hurt(size_t damage);
  static void LoseEnergy(size_t energy_);
  static void GainEnergy(size_t energy_);
  static void SetLastSafePos(glm::vec4 pos);
  static glm::vec4 const& GetLastSafePos();
  static void ResetPlayerPos();

  //Getters
  static EntityID GetPlayerID();
  static size_t GetHealth();
  static size_t GetEnergy();
  static PlayerStateMachine::_PlayerStateMachinestate GetCurrentState();
  static bool FacingRight();
  static float GetTopXSpeed();
  static float GetTopYSpeed();
  static float GetGravity();
  static float GetJumpLaunchSpeed();

  friend Behavior<EntityManager::Type::Player>;
  friend PlayerStateMachine;

private:
  //TODO::Deserialize Player Data
  static EntityID playerID;
  static size_t health;
  static size_t energy;

  //Hurt Data
  static bool HurtFromRight;
  static float HurtSpeed;
  static float HurtTime;
  static float HurtDir;
  static Timer HurtTimer;

  static Timer DashCooldown;
  static PlayerStateMachine::_PlayerStateMachinestate currState;

  static float TopXSpeed;
  static float TopYSpeed;
  static float JumpLaunchSpeed;
  static float Gravity;

  // Last safe position for hazard damage reset
  static glm::vec4 lastSafePos;

  //Cheats
  static bool isInvincible;
};

template<>
class Behavior<EntityManager::Type::Player> : public BaseBehavior
{
public:
  Behavior(EntityID id);
  ~Behavior() override;
  void Update() override;
  void Serialize(std::ofstream& stream) override;
  void Deserialize(rapidjson::Value& object, EntityID ID, const char* filePath) override;

  void OnCollide(const Event<EventType::Collision>& info);
  EventListener<EventType::Collision> listener;

private:
  // State machine
  PlayerStateMachine player_state_;

  // State OnCollide event
  //TODO: event system
  void OnCollideGrounded(const Event<EventType::Collision>& info);
  void OnCollideAirborne(const Event<EventType::Collision>& info);
  void OnCollideDash(const Event<EventType::Collision>& info);

  enum class ABSTRACT_DIR
  {
    TOP,
    LEFT,
    RIGHT,
    BOTTOM,
    INVALID
  };

  glm::vec2 CalculateResolveAngle(const Event<EventType::Collision>& info) const;
  ABSTRACT_DIR GetAbstractDirection(float angle) const;
  bool IsDirectionRight(float angle) const;

};
