#include <UWUEngine/GamePlay/FangBehavior.h>
#include <UWUEngine/FrameRateController.h>
#include <UWUEngine/Component/TransformComponentManager.h>
#include <UWUEngine/Serialization.h>

Behavior<EntityManager::Type::Fang_>::Behavior(EntityID ID) :
  BaseBehavior(ID), listener(MemberFunc(&Behavior<EntityManager::Type::Fang_>::OnCollide), ID)
{
  EventSystem::Register(listener);
}

Behavior<EntityManager::Type::Fang_>::~Behavior()
{
  EventSystem::UnRegister(listener);
}

void Behavior<EntityManager::Type::Fang_>::Serialize(std::ofstream & stream)
{
  stream << ",\n";
  stream << Tabs::TWO;
  stream << "\"behavior\": true";
}

void Behavior<EntityManager::Type::Fang_>::Update()
{
  UpdateState(FrameRateController::GetDeltaTime<float>());
}

void Behavior<EntityManager::Type::Fang_>::Render()
{
}

void Behavior<EntityManager::Type::Fang_>::Deserialize(rapidjson::Value & object, EntityID ID, const char* filePath)
{

}

void Behavior<EntityManager::Type::Fang_>::OnCollide(const Event<EventType::Collision>& info)
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

  case EntityManager::Type::Solid:
  {
    // Check if Fang is within one frame's travel distance away from the ledge

    // Get their translations and scales
    glm::vec4 fangTranslation = TransformComponentManager::GetTranslation(GetID());
    glm::vec4 solidTranslation = TransformComponentManager::GetTranslation(otherObject);
    glm::vec3 fangScale = TransformComponentManager::GetScale(GetID());
    glm::vec3 solidScale = TransformComponentManager::GetScale(otherObject);

    float difference;

    // Check if Fang is facing right or left
    if (TransformComponentManager::GetScale(GetID()).x < 0)
    {
      // Facing left, check against left edge of the solid
      // Calculate the difference between the left edge of Fang and the left edge of the solid
      difference = abs(abs(fangTranslation.x - fangScale.x) - abs(solidTranslation.x - solidScale.x));
    }
    else
    {
      // Facing right, check against right edge of the solid
      difference = abs(abs(solidTranslation.x + solidScale.x) - abs(fangTranslation.x + fangScale.x));
    }

    // Check if the difference is within one frame's travel distance
    if (difference <= walkSpeed * FrameRateController::GetDeltaTime<float>())
    {
      // Flip Fang around to walk away from the ledge
      fangScale.x *= -1.0f;
    }

    break;
  }

  default:
  {
    // Don't do anything
    break;
  }

  }
}

// TODO:Functions to be implemented in other files in the future
// They are currently here to suppress compiler
#pragma region PlaceHolder

void Behavior<EntityManager::Type::Fang_>::Enter_Charge()
{
}

void Behavior<EntityManager::Type::Fang_>::Load_Charge()
{
}

void Behavior<EntityManager::Type::Fang_>::Update_Charge(float dt)
{
}

void Behavior<EntityManager::Type::Fang_>::Unload_Charge()
{
}

void Behavior<EntityManager::Type::Fang_>::Exit_Charge()
{
}

void FangStateMachine::Enter_Hurt()
{
}

void FangStateMachine::Enter_Running()
{
}

void FangStateMachine::Enter_Charge()
{
}

void FangStateMachine::Load_Hurt()
{
}

void FangStateMachine::Load_Running()
{
}

void FangStateMachine::Load_Charge()
{
}

void FangStateMachine::Update_Hurt(float dt)
{
}

void FangStateMachine::Update_Running(float dt)
{
}

void FangStateMachine::Update_Charge(float dt)
{
}

void FangStateMachine::Unload_Hurt()
{
}

void FangStateMachine::Unload_Running()
{
}

void FangStateMachine::Unload_Charge()
{
}

void FangStateMachine::Exit_Hurt()
{
}

void FangStateMachine::Exit_Running()
{
}

void FangStateMachine::Exit_Charge()
{
}

void FangStateMachine::Load_Grounded()
{
}

void FangStateMachine::Enter_Grounded()
{
}

void FangStateMachine::Update_Grounded(float dt)
{
}

void FangStateMachine::Exit_Grounded()
{

}

void FangStateMachine::Unload_Grounded()
{

}
#pragma endregion