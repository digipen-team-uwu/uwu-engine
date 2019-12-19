#pragma once
#include <UWUEngine/Component/BehaviorComponentManager.h>

template<>
class Behavior<EntityManager::Type::DebugVector> : public BaseBehavior
{
public:
  Behavior() : BaseBehavior() { }
  void Render();
private:
};

template<>
class Behavior<EntityManager::Type::DebugRect> : public BaseBehavior
{
public:
  Behavior() : BaseBehavior() {}
	void Render();
private:
};