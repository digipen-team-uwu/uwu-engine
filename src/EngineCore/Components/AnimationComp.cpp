/******************************************************************************/
/*!
\par        Project Umbra
\file       AnimationComponentManager.cpp
\author     Hadi Alhussieni
\date       2019/09/20
\brief      Managing transform components

Copyright � 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#include <UWUEngine/Component/AnimationComp.h>
#include <UWUEngine/Systems/AnimationSys.h>


#include <UWUEngine/Helper.h>
#include <UWUEngine/constants.h>
#include <UWUEngine/Systems/FrameLimiterSys.h>
#include <UWUEngine/Component/TextureComp.h>
#include <fstream>

namespace goc = GameObjectConstants;
using namespace UWUEngine;

AnimationComp::AnimationData& AnimationComp::GetCurrentData(EntityID id)
{
  auto &anim = animations[id];
  return anim.data[anim.currentAnimation];
}

AnimationComp::AnimationData& AnimationComp::GetData(EntityID id, int accessID)
{
  return animations[id].data[accessID];
}

void AnimationComp::AddNewAnimation(EntityID id, int accessID)
{
  animations[id].data[accessID] = AnimationData();
  animations[id].ids.push_back(accessID);
  animations[id].currentAnimation = accessID;
}

void AnimationComp::SetCurrentAnimation(int currentAnimation, EntityID id)
{
  animations[id].currentAnimation = currentAnimation;
}


/*
//TODO: remove accessID from id vector
void  AnimationComponentManager::DeleteAnimation(EntityID id)
{
  auto& currAnim = animations[id];
  currAnim.data.erase(currAnim.currentAnimation);
}

void  AnimationComponentManager::DeleteAnimation(EntityID id, int accessID)
{
  auto& currAnim = animations[id];
  currAnim.data.erase(accessID);
}
*/

void AnimationComp::Play(EntityID id, int accessID)
{
  if (accessID != -1)
  {
    SetCurrentAnimation(accessID, id);
  }
  auto &currAnim = animations[id];
  auto &data = currAnim.data[currAnim.currentAnimation];
    data.frameDelay_ = data.frames_[0].frameDuration;
    auto &text = Get<TextureComp>();
    text.getTexture(id).SetUVS(AnimationSys::indexToUvs(&text, id, data.frames_[0].index));
    data.currentFrame_ = 0;
    data.isRunning_ = true;
}

bool AnimationComp::AnimationFinished(EntityID id)
{
  auto& data = GetCurrentData(id);
  if (data.isRunning_ == false)
    return true;
  return false;
}




void  AnimationComp::AddFrame(int index, float duration, EntityID id, int accessID)
{
  auto& data = GetData(id, accessID);
  data.frames_.push_back(AnimationData::Frame{ index, duration });
  ++(data.frameCount_);
}



void  AnimationComp::SetCurrentFrameIndex(int index, EntityID id, int accessID)
{
  GetData(id, accessID).currentFrame_ = index;
}


void  AnimationComp::SetLooping(bool looping, EntityID id, int accessID)
{
  GetData(id, accessID).looping_ = true;
}



void AnimationComp::InitObject(EntityID id)
{
}

void AnimationComp::ShutdownObject(EntityID id)
{
  animations.erase(id);
}

int AnimationComp::GetCurrentFrameIndex(EntityID ID)
{
    return GetCurrentData(ID).currentFrame_;
}

int AnimationComp::GetCurrentFrame(EntityID ID)
{
  auto& anim = GetCurrentData(ID);
  if (anim.isRunning_)
  {
    return anim.frames_[anim.currentFrame_].index;
  }
  else
  {
    return anim.frames_[anim.frameCount_ - 1].index;
  }
}

void AnimationComp::AddAnimationData(EntityID id, AnimationData data, int accessID)
{
  data.frameCount_ = static_cast<int>(data.frames_.size());
  animations[id].data[accessID] = data;
}

void AnimationComp::AddAnimationDatas(EntityID id, const std::array<AnimationData, goc::MAX_SPRITES>& data)
{
  animations[id].data = data;
}

// The below code was written by Michael Rollosson Halbhuber
