/******************************************************************************/
/*!
\par        Project Umbra
\file       PerceptionBehavior.cpp
\author     Michael Rollosson Halbhuber
\date       2019/11/22
\brief      Implements the behaviors for the Perception Enemy Type (immobile snake)

Copyright © 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#include <UWUEngine/GamePlay/PerceptionBehavior.h>
#include <UWUEngine/FrameLimiterSys.h>
#include <UWUEngine/Serialization.h>
#include <UWUEngine/Physics/Colliders/ColliderPolygon.h>
#include <UWUEngine/Component/ColliderComponentManager.h>

Collider* Behavior<EntityManager::Type::Perception>::idleCollider;
Collider* Behavior<EntityManager::Type::Perception>::attackCollider;

Behavior<EntityManager::Type::Perception>::Behavior(EntityID ID):
BaseBehavior(ID), listener(MemberFunc(&Behavior<EntityManager::Type::Perception>::OnCollide), ID)
{
  if (!idleCollider)
  {
    ColliderPolygon* idle_ = new ColliderPolygon(0, {0, 0});
    idle_->InsertVertex({0.3, -0.5});
    idle_->InsertVertex({0.3, 0.4});
    idle_->InsertVertex({0, 0.5});
    idle_->InsertVertex({-0.5, 0.4});
    idle_->InsertVertex({-0.3, -0.5});
    idleCollider = idle_;
  }
  if (!attackCollider)
  {
    ColliderPolygon* attack_ = new ColliderPolygon(0, {0, 0});
    attack_->InsertVertex({0.3, -0.5});
    attack_->InsertVertex({0,0});
    attack_->InsertVertex({-1.0, -0.25});
    attack_->InsertVertex({-0.3, -0.5});
    attackCollider = attack_;
  }
  ColliderComp::Activate(ID);
  ColliderComp::SetCollider(ID, idleCollider);

  EventSystem::Register(listener);
}

Behavior<EntityManager::Type::Perception>::~Behavior()
{
  EventSystem::UnRegister(listener);
}

void Behavior<EntityManager::Type::Perception>::Update()
{
    UpdateState(FrameRateController::GetDeltaTime<float>());
}

void Behavior<EntityManager::Type::Perception>::Render()
{
    // Ignore, only exists to suppress compiler errors
}

void Behavior<EntityManager::Type::Perception>::Serialize(std::ofstream& stream)
{
  stream << ",\n";
  stream << Tabs::TWO;
  stream << "\"behavior\": true";
}

void Behavior<EntityManager::Type::Perception>::Deserialize(rapidjson::Value& object, EntityID ID, const char* filePath)
{
    // Check for the health member
    if (object.HasMember("health"))
    {
        // Checking that health is an unsigned int
        assert(object["health"].IsUint());
        health = object["health"].GetUint();
    }
}

void Behavior<EntityManager::Type::Perception>::OnCollide(const Event<EventType::Collision>& info)
{
    // Figure out which object is the other object
    EntityID otherObject;
    if (info.obj1 == GetID())
    {
        otherObject = info.obj2;
    }
    else
    {
        otherObject = info.obj1;
    }

    switch (EntityManager::GetType(otherObject))
    {
    case EntityManager::Type::Player:
    {
        // Check if the player is dashing
        if (PlayerData::GetCurrentState() == PlayerStateMachine::_PlayerStateMachinestate::Dash)
        {
            SetNextState(Hurt);
        }
        // Don't do anything otherwise, it's on the player's behavior now
        break;
    }

    default:
    {
        // Don't do anything
        break;
    }

    }
}

void Behavior<EntityManager::Type::Perception>::SetHealth(size_t amount)
{
    health = amount;
}

#pragma region BaseState
void PerceptionStateMachine::Enter_Hurt()
{
}

void PerceptionStateMachine::Enter_Attack()
{
}

void PerceptionStateMachine::Enter_Idle()
{
}

void PerceptionStateMachine::Load_Hurt()
{
}

void PerceptionStateMachine::Load_Attack()
{
}

void PerceptionStateMachine::Load_Idle()
{
}

void PerceptionStateMachine::Update_Hurt(float dt)
{
}

void PerceptionStateMachine::Update_Attack(float dt)
{
}

void PerceptionStateMachine::Update_Idle(float dt)
{
}

void PerceptionStateMachine::Unload_Hurt()
{
}

void PerceptionStateMachine::Unload_Attack()
{
}

void PerceptionStateMachine::Unload_Idle()
{
}

void PerceptionStateMachine::Exit_Hurt()
{
}

void PerceptionStateMachine::Exit_Attack()
{
}

void PerceptionStateMachine::Exit_Idle()
{
}
#pragma endregion 
