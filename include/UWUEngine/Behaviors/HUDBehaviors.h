#pragma once
#include <UWUEngine/Component/BehaviorComponentManager.h>

template<>
class Behavior<EntityManager::Type::HUDHealth> : public BaseBehavior
{
public:
  Behavior(EntityID id) : BaseBehavior(id), health(0) { }
  void Render();
  void SetHealth(size_t newHealth) { health = newHealth; }
private:
  size_t health;
};

template<>
class Behavior<EntityManager::Type::HUDEnergy> : public BaseBehavior
{
public:
  Behavior(EntityID id);
  void Update();
  void Render();
  void SetEnergy(size_t newEnergy) { energy = newEnergy; }
private:
  size_t energy;
};

