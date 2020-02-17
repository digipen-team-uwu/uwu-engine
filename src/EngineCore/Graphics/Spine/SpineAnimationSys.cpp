#include <UWUEngine/Systems/SpineAnimationSys.h>
#include <UWUEngine/Systems/FrameLimiterSys.h>
#include <UWUEngine/Systems/CompSpaceSys.h>
#include <UWUEngine/Component/SpineAnimationComp.h>
#include <UWUEngine/Component/SpineSkeletonComp.h>

using namespace UWUEngine;

void SpineAnimationSys::Update()
{
  auto& compSys = Get<CompSpaceSys>();
	UpdateSpace(
	compSys.space_gameplay.Get<SpineAnimationComp>(), 
	compSys.space_gameplay.Get<SpineSkeletonComp>());
}

void SpineAnimationSys::UpdateSpace(SpineAnimationComp& animComp, SpineSkeletonComp& skelComp)
{
	for (auto i = animComp.Begin(); i != animComp.End(); ++i)
	{
    if (!i->second.GetAnimationState())
    {
      continue;
    }
		EntityID ID = i->first;
		spAnimationState* animationState = i->second.GetAnimationState();
		// TODO::make this singleton
		spSkeleton* skeleton = skelComp.GetSkeleton(ID).GetSkeleton();

	  i->second.UpdateAnimation(Get<FrameLimiterSys>().GetDeltaTime<float>() * 1.5f);
		spAnimationState_apply(animationState, skeleton);
		spSkeleton_updateWorldTransform(skeleton);
	}
}
