#include <UWUEngine/Systems/ColliderSys.h>

#include <UWUEngine/Systems/PhysicsSys.h>
#include <UWUEngine/Systems/LogSys.h>
#include <UWUEngine/Systems/CompSpaceSys.h>
#include <UWUEngine/Systems/FrameLimiterSys.h>
#include <UWUEngine/Component/ColliderComp.h>

using namespace UWUEngine;

ColliderSys::ColliderSys(ISpace* p) :
  System(p)
{

}

void ColliderSys::Update()
{
  auto& compSys = Get<CompSpaceSys>();
  auto& gameplaySpace = compSys.space_gameplay;
  auto& colliderComp = gameplaySpace.Get<ColliderComp>();
  auto& physicsComp = gameplaySpace.Get<PhysicsComp>();

  //Detection and Resolution
  for (auto i = colliderComp.begin(); i != colliderComp.end(); ++i)
  {
    BodyType type1 = physicsComp.getPhysics(i->first).GetBodyType();
    for (auto j = std::next(i); j != colliderComp.end(); ++j)
    {
      //Ignore STATIC - STATIC collision
      BodyType type2 = physicsComp.getPhysics(j->first).GetBodyType();
      if (type1 == BodyType::STATIC && type2 == BodyType::STATIC)
      {
        continue;
      }

      //Collision Detection
      const Event<EventType::Collision> event = i->second->IsColliding(*j->second);

      //TODO: event system

      if (event.depth != 0)
      {
        Get<EventSys>().Push(event);
      }
    }
  }
}
