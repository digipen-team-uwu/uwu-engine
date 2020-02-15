/******************************************************************************/
/*!
\par        Project Umbra
\file       AnimationComponentManager.h
\author     Hadi Alhusseieni
\date       2019/09/20
\brief      Managing animations

Copyright � 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#pragma once
#include <vector>
#include <UWUEngine/constants.h>
#include <glm/glm.hpp>
#include <UWUEngine/Component/Component.h>
#include <array>
#include <unordered_map>

namespace UWUEngine
{
class Animations;

  class AnimationComp : public Component<AnimationComp, Animations>
  {
  public:
    AnimationComp(ISpace *parent) : Component(parent){}
    ~AnimationComp() = default;
    void InitObject(EntityID ID) override;
    void ShutdownObject(EntityID id) override;
    /* when this is called, a new animation is made and set to the current animation,
      so any proceeding addframes calls will correspond to the newest animation.
      You only need to call this if you want more than one animation on a single ID */
    void AddNewAnimation(EntityID id, int accessID);
    void SetCurrentAnimation(int accessID, EntityID id);
    void AddFrame(int index, float duration, EntityID id, int accessID);
    void SetCurrentFrameIndex(int index, EntityID id, int accessID);
    void SetLooping(bool looping, EntityID id, int accessID);

    int GetCurrentFrameIndex(EntityID id);
    int GetCurrentFrame(EntityID ID);



    /*   implement if we ever need it

    float GetCurrentFrameDelay(EntityID id);
    bool GetLooping(EntityID id);

    const std::array<std::pair<int, float>, goc::MAX_ANIMATION_FRAME_COUNT>& GetFrameSequence(EntityID id);
    float GetDefaultFrameDelay(EntityID id);
    const glm::uvec2& GetSheetDimensions(EntityID id); */

    /*
    static void DeleteAnimation(EntityID id);
    static void DeleteAnimation(EntityID id, int accessID);
    */

    //plays current animation (last one set or enabled) by default. only pass second param if multiple anims are loaded on obj
    //if you pass an animation number, the current animation on the object will be set to that
    void Play(EntityID ID, int accessID = -1);
  
    bool AnimationFinished(EntityID id);

    struct AnimationData
    {
      struct Frame
      {
        int index;
        float frameDuration;
      };
      std::vector<Frame> frames_;
      bool looping_;
      int currentFrame_;
      int frameCount_;
      float frameDelay_;
      bool isRunning_;
    };

    struct Animations
    {
      int currentAnimation;
      //each animation can have a specific sequence of frames, stored as a vector of pairs. 
      //First int is the index into the spritesheet, second is the frame duration
      //each object can have a vector of animations consisting of a vector of frames 
      std::vector<int> ids;
      std::array<AnimationData, GameObjectConstants::MAX_SPRITES> data;
    };
    void AddAnimationData(EntityID id, AnimationData data, int accessID);
    void AddAnimationDatas(EntityID id, const std::array<AnimationData, GameObjectConstants::MAX_SPRITES>& data);
  private:
    AnimationData& GetData(EntityID id, int accessID);
    AnimationData& GetCurrentData(EntityID id);
    //the int in the pair is the current animation id for the animation vector
    friend class Editor;
    friend class AnimationSys;
    std::unordered_map<EntityID, Animations> animations;
  };
}
