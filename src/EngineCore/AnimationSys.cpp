#include <UWUEngine/Systems/AnimationSys.h>
#include <UWUEngine/Component/EntityComp.h>
#include <UWUEngine/Component/TextureComp.h>
#include <UWUEngine/Systems/FrameLimiterSys.h>
#include <vector>
#include "UWUEngine/Component/AnimationComp.h"
#include <UWUEngine/Systems/CompSpaceSys.h>

using namespace UWUEngine;

namespace UWUEngine
{
  using EntityID = unsigned;
}

void AnimationSys::Update()
{
  auto& comp = Get<CompSpaceSys>();
  UpdateAnimations(dynamic_cast<ISpace*>(&(comp.space_environment)));
  UpdateAnimations(dynamic_cast<ISpace*>(&(comp.space_ui)));
  UpdateAnimations(dynamic_cast<ISpace*>(&(comp.space_particle)));
  UpdateAnimations(dynamic_cast<ISpace*>(&(comp.space_debug)));
}

glm::vec2 AnimationSys::indexToUvs(ISpace * space, EntityID id, int index)
{
  auto* texComp = static_cast<TextureComp*>(space->GetObject(static_cast<unsigned>(GetOrder<TextureComp>())));
  const auto texture = texComp->getTexture(id);
  auto &dim = texture.GetDimension();
  float u = 1.0f / dim.x * (index % dim.y);
  float v = (1.0f / dim.y) * (static_cast<float>(index) / dim.x);
  return { u, v };
}

glm::vec2 AnimationSys::indexToUvs(TextureComp* texComp, EntityID id, int index)
{
  const auto texture = texComp->getTexture(id);
  auto& dim = texture.GetDimension();
  float u = 1.0f / dim.x * (index % dim.y);
  float v = (1.0f / dim.y) * (static_cast<float>(index) / dim.x);
  return { u, v };
}

void AnimationSys::UpdateAnimations(ISpace* space)
{
  std::vector<EntityID> ids = static_cast<EntityComp *>(space->GetObject(static_cast<unsigned>(GetOrder<EntityComp>())))->GetIDs();
  auto* animComp = static_cast<AnimationComp*>(space->GetObject(static_cast<unsigned>(GetOrder<AnimationComp>())));
  auto* texComp = static_cast<TextureComp*>(space->GetObject(static_cast<unsigned>(GetOrder<TextureComp>())));
  for (auto it : ids)
  {
    auto &data = animComp->GetCurrentData(it);
    if (data.isRunning_)
    {
      data.frameDelay_ -= Get<FrameLimiterSys>().GetDeltaTime<float>();
      if (data.frameDelay_ < 0)
      {
        ++data.currentFrame_;
        if (data.currentFrame_ < data.frameCount_)
        {
          data.frameDelay_ = data.frames_[data.currentFrame_].frameDuration;
          texComp->getTexture(it).SetUVS(indexToUvs(texComp, it, data.frames_[data.currentFrame_].index));
        }
        else if (data.looping_)
        {
          data.currentFrame_ = 0;
          texComp->getTexture(it).SetUVS(indexToUvs(texComp, it, data.frames_[0].index));
          data.frameDelay_ = data.frames_[0].frameDuration;
        }
        else
        {
          data.isRunning_ = false;
        }
      }
    }
  }
}