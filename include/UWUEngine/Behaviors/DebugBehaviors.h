#pragma once
#include <UWUEngine/Component/BehaviorComponentManager.h>

template<>
class Behavior<EntitySys::Type::DebugVector> : public BaseBehavior
{
public:
  Behavior() : BaseBehavior() { }
  void Render();
private:
};

template<>
class Behavior<EntitySys::Type::DebugRect> : public BaseBehavior
{
public:
  Behavior() : BaseBehavior() {}
	void Render();
private:
};