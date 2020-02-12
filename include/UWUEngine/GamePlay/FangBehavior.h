/******************************************************************************/
/*!
\par        Project Umbra
\file       FangBehavior.h
\author     Yi Qian
\date       2019/12/05
\brief      Fang Behavior,I hate file header comments 

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#pragma once

#include <UWUEngine/statemachine.hpp>
#include <UWUEngine/Physics/Colliders/Collider.h>
#include <UWUEngine/Component/BehaviorComp.h>

StateMachine(Fang, false, Grounded, Charge, Running, Hurt);

template<>
class Behavior<EntitySys::Type::Fang_>: public BaseBehavior, public FangStateMachine
{
public:
    Behavior(EntityID ID);
	~Behavior() override;
  void Serialize(std::ofstream& stream) override;
	void Update() override;
	void Render() override;
	void Deserialize(rapidjson::Value& object, EntityID ID, const char* filePath) override;
    void OnCollide(const Event<EventType::Collision>& info);
		EventListener<EventType::Collision> listener;

#pragma region StateDeclarations
	void Enter_Hurt() override;
	void Enter_Running() override;
	void Enter_Charge() override;
	void Enter_Grounded() override;
	void Load_Hurt() override;
	void Load_Running() override;
	void Load_Charge() override;
	void Load_Grounded() override;
	void Update_Hurt(float dt) override;
	void Update_Running(float dt) override;
	void Update_Charge(float dt) override;
	void Update_Grounded(float dt) override;
	void Unload_Hurt() override;
	void Unload_Running() override;
	void Unload_Charge() override;
	void Unload_Grounded() override;
	void Exit_Hurt() override;
	void Exit_Running() override;
	void Exit_Charge() override;
	void Exit_Grounded() override;
#pragma endregion 

private:
	size_t health = 1;

    // Walk speed is needed in multiple places so I've stored it as a private variable
    // Const for now depending on how we want to handle it in the future
    const float walkSpeed = 1000.0f;

    float hurtTimeRemaining{};
};
