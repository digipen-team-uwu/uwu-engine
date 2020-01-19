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

#include <UWUEngine/Component/AnimationComponentManager.h>

template<>
size_t RegisterComponentHelper<AnimationComponentManager>::RegisterComponentHelper_ID = EntityManager::AddComponent<AnimationComponentManager>(ComponentUpdateOrder::Animation);

#include <UWUEngine/Helper.h>
#include <UWUEngine/constants.h>
#include <UWUEngine/FrameRateController.h>
#include <UWUEngine/Entity/EntityManager.h>
#include <UWUEngine/Component/TextureComponentManager.h>
#include <fstream>
#include <UWUEngine/Serialization.h>

namespace goc = GameObjectConstants;

std::unordered_map<EntityID, AnimationComponentManager::Animations> AnimationComponentManager::animations;

AnimationComponentManager::AnimationData& AnimationComponentManager::GetCurrentData(EntityID id)
{
  auto &anim = animations[id];
  return anim.data[anim.currentAnimation];
}

AnimationComponentManager::AnimationData& AnimationComponentManager::GetData(EntityID id, int accessID)
{
  return animations[id].data[accessID];
}

void AnimationComponentManager::AddNewAnimation(EntityID id, int accessID)
{
  animations[id].data[accessID] = AnimationData();
  animations[id].ids.push_back(accessID);
  animations[id].currentAnimation = accessID;
}

void AnimationComponentManager::SetCurrentAnimation(int currentAnimation, EntityID id)
{
  animations[id].currentAnimation = currentAnimation;
}

void AnimationComponentManager::Update()
{
    std::vector<EntityID> ids = EntityManager::GetIDs();
    auto it = ids.begin();
    while (it != ids.end())
    {
      
        if (AnimationComponentManager::IsActive(*it))
        {
            AnimationData& data = GetCurrentData(*it);
            if (data.isRunning_)
            {
              data.frameDelay_ -= FrameRateController::GetDeltaTime<float>();
              if (data.frameDelay_ < 0)
              {
                ++data.currentFrame_;
                if (data.currentFrame_ < data.frameCount_)
                {
                  data.frameDelay_ = data.frames_[data.currentFrame_].frameDuration;
                  TextureComponentManager::SetUV(*it, indexToUvs(*it, data.frames_[data.currentFrame_].index));
                }
                else if (data.looping_)
                {
                  data.currentFrame_ = 0;
                  TextureComponentManager::SetUV(*it, indexToUvs(*it, data.frames_[0].index));
                  data.frameDelay_ = data.frames_[0].frameDuration;
                }
                else
                {
                  data.isRunning_ = false;
                }
              }
            }
        }
        ++it;
    }
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

void AnimationComponentManager::Play(EntityID id, int accessID)
{
  if (accessID != -1)
  {
    SetCurrentAnimation(accessID, id);
  }
  auto &currAnim = animations[id];
  auto &data = currAnim.data[currAnim.currentAnimation];
    data.frameDelay_ = data.frames_[0].frameDuration;
    TextureComponentManager::SetUV(id, indexToUvs(id, data.frames_[0].index));
    data.currentFrame_ = 0;
    data.isRunning_ = true;
}

bool AnimationComponentManager::AnimationFinished(EntityID id)
{
  auto& data = GetCurrentData(id);
  if (data.isRunning_ == false)
    return true;
  return false;
}

glm::vec2 AnimationComponentManager::indexToUvs(EntityID id, int index)
{
   
    float u = (1.0f / TextureComponentManager::GetDimensions(id).x) * (index % TextureComponentManager::GetDimensions(id).x);
    float v = (1.0f / TextureComponentManager::GetDimensions(id).y) * (index / TextureComponentManager::GetDimensions(id).x);
    return { u, v };
}


void  AnimationComponentManager::AddFrame(int index, float duration, EntityID id, int accessID)
{
  auto& data = GetData(id, accessID);
  data.frames_.push_back(AnimationData::Frame{ index, duration });
  ++(data.frameCount_);
}



void  AnimationComponentManager::SetCurrentFrameIndex(int index, EntityID id, int accessID)
{
  GetData(id, accessID).currentFrame_ = index;
}


void  AnimationComponentManager::SetLooping(bool looping, EntityID id, int accessID)
{
  GetData(id, accessID).looping_ = true;
}



void AnimationComponentManager::InitObject(EntityID id)
{
}

void AnimationComponentManager::ShutdownObject(EntityID id)
{
  animations.erase(id);
}

int AnimationComponentManager::GetCurrentFrameIndex(EntityID ID)
{
    return GetCurrentData(ID).currentFrame_;
}

int AnimationComponentManager::GetCurrentFrame(EntityID ID)
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

void AnimationComponentManager::AddAnimationData(EntityID id, AnimationData data, int accessID)
{
  data.frameCount_ = static_cast<int>(data.frames_.size());
  animations[id].data[accessID] = data;
}

void AnimationComponentManager::AddAnimationDatas(EntityID id, const std::array<AnimationData, goc::MAX_SPRITES>& data)
{
  animations[id].data = data;
}

// The below code was written by Michael Rollosson Halbhuber
void AnimationComponentManager::Serialize(std::ofstream& stream, EntityID id)
{
    // Check for an active animation component
    if (AnimationComponentManager::IsActive(id))
    {
      auto& anim = animations[id];
        // Set boolalpha
        stream.setf(std::ios::boolalpha);

        // Begin the animation object
        stream << "\"animation\" :\n";
        stream << Tabs::TWO <<"{";

        stream << Tabs::THREE <<"\"animations\" :\n[";
        //stream << Tabs::THREE << "[";

        for (auto it : anim.ids)
        {
          stream << Tabs::THREE << "{ ";
          auto& data = anim.data[it];
          stream << Tabs::FOUR << "\"id\" : " << it << ",\n";

          // Begin the frames array
          stream << Tabs::FIVE << "\"frames\" :\n[";
          //stream << "[";

          // Loop through the frames in the animation, printing an object for each one
          for (int i = 0; i < data.frameCount_; ++i)
          {
            // Open the animation frame
            stream << Tabs::SIX << "{ ";

            // Print the index name/value pair (lines split up for clarity
            stream << Tabs::SIX << "\"index\" : " << data.frames_[i].index << ", ";
            stream << "\"duration\" : " << data.frames_[i].frameDuration << " ";

            // Close the animation frame
            stream << "}";

            // Check if it is the last object in the array
            if (i != data.frameCount_ - 1)
            {
              // It isn't, print a comma
              stream << ",";
            }

            // Print a newline
            stream << "\n";
          }

          // Close out the array
          stream << Tabs::THREE << "],\n";

          // Print the looping value
          stream << Tabs::THREE << "\"looping\" : " << data.looping_ << ",\n";

          // Print the current frame
          stream << Tabs::THREE << "\"current frame\" : " << data.currentFrame_ << ",\n";

          // Print the running bool
          stream << Tabs::THREE << "\"running\" : " << data.isRunning_ << "\n";

          // Close the object
          stream << Tabs::TWO << "}";

          // Check if it is the last object in the array
          if (it != anim.ids.back())
          {
            // It isn't, print a comma
            stream << ",";
          }
          
        }
        stream << "]\n";
        // Close the object
        stream << "}";
    }
}

