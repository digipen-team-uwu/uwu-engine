/******************************************************************************/
/*!
\par        Project Umbra
\file       PerceptionBehavior.h
\author     Michael Rollosson Halbhuber
\date       2019/11/22
\brief      Lays out the behaviors for the Perception Enemy Type (immobile snake)

Copyright © 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#pragma once
#include <UWUEngine/Component/BehaviorComponentManager.h>
#include <UWUEngine/statemachine.hpp>
#include <UWUEngine/Physics/Colliders/Collider.h>

StateMachine(Perception, false, Idle, Attack, Hurt);

template<>
class Behavior<EntitySys::Type::Perception> : public BaseBehavior, public PerceptionStateMachine
{
public:
    Behavior(EntityID ID);
    ~Behavior() override;
    void Update() override;
    void Render() override;
    void Serialize(std::ofstream& stream) override;
    void Deserialize(rapidjson::Value& object, EntityID ID, const char* filePath) override;
    void OnCollide(const Event<EventType::Collision>& info);
    EventListener<EventType::Collision> listener;
    void SetHealth(size_t amount);

#pragma region StateDeclarations
    void Enter_Idle() override;
    void Enter_Attack() override;
    void Enter_Hurt() override;
    void Load_Hurt() override;
    void Load_Idle() override;
    void Load_Attack() override;
    void Update_Hurt(float dt) override;
    void Update_Idle(float dt) override;
    void Update_Attack(float dt) override;
    void Unload_Hurt() override;
    void Unload_Idle() override;
    void Unload_Attack() override;
    void Exit_Hurt() override;
    void Exit_Idle() override;
    void Exit_Attack() override;
#pragma endregion 

private:
    size_t health = 4;
    float attackTimeRemaining{};
    float stunTimeRemaining{};

    static Collider* idleCollider;
    static Collider* attackCollider;
};