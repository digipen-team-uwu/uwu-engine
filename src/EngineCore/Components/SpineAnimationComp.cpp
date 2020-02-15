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
#include <UWUEngine/Systems/LogSys.h>
#include <UWUEngine/Modules/SpineDataMod.h>
#include <UWUEngine/Component/SpineAnimationComp.h>

namespace UWUEngine
{
  SpineAnimation::SpineAnimation(SpineData& data) :
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

  //TODO: Spine animation system
  //void SpineAnimationComp::Update()
  //{
  //  for (auto& animation : animations)
  //  {
  //    EntityID ID = animation.first;
  //    spAnimationState* animationState = animation.second.GetAnimationState();
  //    spSkeleton* skeleton = SpineSkeletonComponentManager::GetSkeleton(ID).GetSkeleton();

  //    animation.second.UpdateAnimation(FrameRateController::GetDeltaTime<float>() * 1.5f);
  //    spAnimationState_apply(animationState, skeleton);
  //    spSkeleton_updateWorldTransform(skeleton);
  //  }
  //}

  void SpineAnimationComp::InitObject(EntityID ID)
  {
  }

  void SpineAnimationComp::ShutdownObject(EntityID ID)
  {
    SpineAnimation& animation = GetAnimation(ID);

    animations.erase(ID);
  }

  void SpineAnimationComp::SetAnimation(EntityID ID, SpineData& data)
  {
    if (animations.find(ID) != animations.end())
    {
      Get<LogSys>().Log(Get<LogSys>().DEBUG) << "Spine Animation component already exists for object: " << ID << std::endl;
      Get<LogSys>().Log(Get<LogSys>().DEBUG) << "Spine Animation component updated" << std::endl;
    }
    animations.insert_or_assign(ID, SpineAnimation(data));
  }

  void SpineAnimationComp::SetAnimation(EntityID ID, const char* dataName)
  {
    if (animations.find(ID) != animations.end())
    {
      Get<LogSys>().Log(Get<LogSys>().DEBUG) << "Spine Animation component already exists for object: " << ID << std::endl;
      Get<LogSys>().Log(Get<LogSys>().DEBUG) << "Spine Animation component updated" << std::endl;
    }
    animations.insert_or_assign(ID, SpineAnimation(Get<SpineDataMod>().GetData(dataName)));
  }

  SpineAnimation& SpineAnimationComp::GetAnimation(EntityID ID)
  {
    return animations.find(ID)->second;
  }

  std::unordered_map<EntityID, SpineAnimation>::iterator SpineAnimationComp::Begin()
  {
    return animations.begin();
  }

  std::unordered_map<EntityID, SpineAnimation>::iterator SpineAnimationComp::End()
  {
    return animations.end();
  }
}
