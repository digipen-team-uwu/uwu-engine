/******************************************************************************/
/*!
\par        Project Umbra
\file       SpineAnimationComp.h
\author     Yi Qian
\date       2019/12/05
\brief      Spine animation component manager,I hate file header comments

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#pragma once

#include <UWUEngine/Modules/SpineDataMod.h>
#include <UWUEngine/Component/Component.h>
#include <unordered_map>

namespace UWUEngine
{
  //Forward Declaration
  class SpineData;

  //Component
  class SpineAnimation
  {
  public:
    //Constructors
    explicit SpineAnimation();
    explicit SpineAnimation(SpineData& data);

    //Functions
    void UpdateAnimation(float dt) const;
    void ChangeAnimation(const char* animationName, bool isLooping) const;
    void StartPlaying();
    void StopPlaying();
    [[nodiscard]] bool IsPlaying() const;

    //Getters
    [[nodiscard]] spAnimationState* GetAnimationState() const;
    [[nodiscard]] const spAnimationStateData* GetAnimationStateData() const;
    [[nodiscard]] const spSkeletonData* GetSkeletonData() const;

  private:
    //Data
    spAnimationState* animationState;
    bool isPlaying{ true };
  };

  //Component Manager
  class SpineAnimationComp : public Component<SpineAnimationComp, SpineAnimation>
  {
  public:
    SpineAnimationComp(ISpace* p):Component<SpineAnimationComp, SpineAnimation>(p){}
    void InitObject(EntityID ID) override;
    void ShutdownObject(EntityID ID) override;

    void SetAnimation(EntityID ID, SpineData& data);
    void SetAnimation(EntityID ID, const char* dataName);
    SpineAnimation& GetAnimation(EntityID ID);

    std::unordered_map<EntityID, SpineAnimation>::iterator Begin();
    std::unordered_map<EntityID, SpineAnimation>::iterator End();

  private:
    std::unordered_map<EntityID, SpineAnimation> animations;
  };
}