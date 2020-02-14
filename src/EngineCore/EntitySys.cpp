#include <UWUEngine/Systems/EntitySys.h>
#include <UWUEngine/Component/EntityComp.h>
#include <UWUEngine/Systems/Order.h>
using namespace UWUEngine;

void EntitySys::Update()
{
}

EntityID EntitySys::CreateEntity(ISpace *space)
{
  EntityComp* comp = static_cast<EntityComp*>(space->GetObject(static_cast<unsigned int>(GetOrder<EntityComp>())));
  EntityID id = 0;
  auto& free = comp->GetFreeIDs();
  auto& ids = comp->GetIDs();
  if (free.size())
  {
    id = free.top();
    free.pop();
  }
  else
  {
    id = comp->GetIDCount();
    comp->SetIDCount(id + 1);
  }
  ids.push_back(id);
  if (id >= comp->GetVectorSize())
  {
    comp->ResizeVectors();
    //create instances here
  }
  return id;
}

void EntitySys::DestroyEntity(ISpace* space, EntityID id)
{
  EntityComp* comp = static_cast<EntityComp*>(space->GetObject(static_cast<unsigned>(GetOrder<EntityComp>())));
  comp->SetDestroyed(id);
}