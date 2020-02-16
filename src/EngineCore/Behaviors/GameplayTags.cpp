#include <UWUEngine/Behaviors/GameplayTags.h>
#include <UWUEngine/Component/PhysicsComp.h>
using namespace UWUEngine;


void Behavior<EntityComp::FALLS>::Update()
{
  Physics &physics = Get<PhysicsComp>().getPhysics(GetID());
  physics.SetAcceleration({ 0, -800, 0, 1 });
}
