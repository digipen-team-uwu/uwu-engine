#include <UWUEngine/Systems/BehaviorSys.h>
#include <UWUEngine/Component/BehaviorComp.h>
#include <UWUEngine/Systems/CompSpaceSys.h>

using namespace UWUEngine;

void BehaviorSys::Update()
{
  auto& comp = Get<CompSpaceSys>();
  UpdateBehaviors(dynamic_cast<ISpace*>(&(comp.space_ui)));
  UpdateBehaviors(dynamic_cast<ISpace*>(&(comp.space_particle)));
  UpdateBehaviors(dynamic_cast<ISpace*>(&(comp.space_debug)));
}

void BehaviorSys::UpdateBehaviors(ISpace* space)
{
  auto* behavComp = static_cast<BehaviorComp*>(space->GetObject(static_cast<unsigned>(GetOrder<BehaviorComp>())));
  for(auto it : behavComp->behaviors)
  {
    it.second->Update();
  }
}
