/******************************************************************************/
/*!
\par        Project Umbra
\file       SpineAnimationComponentManager.cpp
\author     Yi Qian
\date       2019/12/05
\brief      Spine animation component manager,I hate file header comments

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#include <UWUEngine/Engine.h>
#include <UWUEngine/FrameRateController.h>
#include <UWUEngine/Component/SpineAnimationComponentManager.h>
#include <UWUEngine/Component/SpineSkeletonComponentManager.h>
#include <UWUEngine/Debugs/TraceLogger.h>


std::unordered_map<EntityID, SpineAnimation> SpineAnimationComponentManager::animations;

SpineAnimation::SpineAnimation(SpineData& data):
animationState(spAnimationState_create(&data.GetAnimationStateData()))
{
}

void SpineAnimation::UpdateAnimation(float dt) const
{
	if (isPlaying)
	{
		spAnimationState_update(animationState, dt);
	}
}

void SpineAnimation::ChangeAnimation(const char* animationName, bool isLooping) const
{
	spAnimationState_setAnimationByName(animationState, 0, animationName, isLooping);
}

void SpineAnimation::StartPlaying()
{
	isPlaying = true;
}

void SpineAnimation::StopPlaying()
{
	isPlaying = false;
}

bool SpineAnimation::IsPlaying() const
{
	return isPlaying;
}

spAnimationState* SpineAnimation::GetAnimationState() const
{
	return animationState;
}

const spAnimationStateData* SpineAnimation::GetAnimationStateData() const
{
	return animationState->data;
}

const spSkeletonData* SpineAnimation::GetSkeletonData() const
{
	return animationState->data->skeletonData;
}

void SpineAnimationComponentManager::Update()
{
	for (auto & animation: animations)
	{
		EntityID ID = animation.first;
		spAnimationState* animationState = animation.second.GetAnimationState();
		// TODO::make this singleton
		spSkeleton* skeleton = SpineSkeletonComponentManager::GetSkeleton(ID).GetSkeleton();

		animation.second.UpdateAnimation(FrameRateController::GetDeltaTime<float>() * 1.5f);
		spAnimationState_apply(animationState, skeleton);
		spSkeleton_updateWorldTransform(skeleton);
	}
}

void SpineAnimationComponentManager::InitObject(EntityID ID)
{
}

void SpineAnimationComponentManager::ShutdownObject(EntityID ID)
{
	SpineAnimation& animation = GetAnimation(ID);
	
	animations.erase(ID);
}

void SpineAnimationComponentManager::SetAnimation(EntityID ID, SpineData& data)
{
	if (animations.find(ID) != animations.end())
	{
    TraceLogger::Log(TraceLogger::DEBUG) << "Spine Animation component already exists for object: " << ID << std::endl;
    TraceLogger::Log(TraceLogger::DEBUG) << "Spine Animation component updated" << std::endl;
	}
	animations.insert_or_assign(ID, SpineAnimation(data));
}

void SpineAnimationComponentManager::SetAnimation(EntityID ID, const char* dataName)
{
	if (animations.find(ID) != animations.end())
	{
		TraceLogger::Log(TraceLogger::DEBUG) << "Spine Animation component already exists for object: " << ID << std::endl;
		TraceLogger::Log(TraceLogger::DEBUG) << "Spine Animation component updated" << std::endl;
	}
	animations.insert_or_assign(ID, SpineAnimation(SpineDataManager::GetData(dataName)));
}

SpineAnimation& SpineAnimationComponentManager::GetAnimation(EntityID ID)
{
	return animations.find(ID)->second;
}
