#include <UWUEngine/Systems/EntitySys.h>
#include <UWUEngine/Component/Component.h>
#include <UWUEngine/Space.h>
#include <UWUEngine/Component/EntityComp.h>
#include <UWUEngine/Systems/Order.h>
#include <UWUEngine/Systems/CompSpaceSys.h>
using namespace UWUEngine;

namespace UWUEngine
{
  class EntityComp;
}

void EntitySys::Update()
{
  auto &comp = Get<CompSpaceSys>();
  CleanDestroyeds(dynamic_cast<ISpace *>(&(comp.space_debug)));
  CleanDestroyeds(dynamic_cast<ISpace*>(&(comp.space_environment)));
  CleanDestroyeds(dynamic_cast<ISpace*>(&(comp.space_gameplay)));
  CleanDestroyeds(dynamic_cast<ISpace*>(&(comp.space_light)));
  CleanDestroyeds(dynamic_cast<ISpace*>(&(comp.space_particle)));
  CleanDestroyeds(dynamic_cast<ISpace*>(&(comp.space_ui)));
}

void EntitySys::CleanDestroyeds(ISpace *space)
{
  auto* entcomp = static_cast<EntityComp *>(space->GetObject(static_cast<unsigned>(GetOrder<EntityComp>())));
  auto& destroyed = entcomp->GetDestroyeds();
  auto& free = entcomp->GetFreeIDs();
  auto& ids = entcomp->GetIDs();
  while (!destroyed.empty())
  {
    EntityID temp = ids.back();
    EntityID dest = destroyed.top();
    destroyed.pop();
    ids[dest] = temp;
    ids.pop_back();
    free.push(dest);
  }
}

EntityID EntitySys::CreateEntity(ISpace *space)
{
  EntityComp* comp = static_cast<EntityComp*>(space->GetObject(static_cast<unsigned int>(GetOrder<EntityComp>())));
  EntityID id = 0;
  auto& free = comp->GetFreeIDs();
  auto& ids = comp->GetIDs();

  if (free.empty())
  {
    id = comp->GetIDCount();
    comp->SetIDCount(static_cast<size_t>(id) + 1);
  }
  else
  {
    id = free.top();
    free.pop();
  }
  
  ids.push_back(id);
  if (id >= comp->GetVectorSize())
  {
    comp->ResizeVectors();
    //create instances here
  }

  const auto component_space = dynamic_cast<IBaseSpace<IComponent>*>(space);
  for (auto component : *component_space)
  {
    component.second->InitObject(id);
  }
  
  return id;
}

void EntitySys::DestroyEntity(ISpace* space, EntityID id)
{
  EntityComp* comp = static_cast<EntityComp*>(space->GetObject(static_cast<unsigned>(GetOrder<EntityComp>())));
  comp->SetDestroyed(id);

  auto component_space = dynamic_cast<IBaseSpace<IComponent>*>(space);
  for (auto component : *component_space)
  {
    component.second->ShutdownObject(id);
  }
}