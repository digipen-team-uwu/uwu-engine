/******************************************************************************/
/*!
\par        Project Umbra
\file       SpineSkeletonComp.h
\author     Yi Qian
\date       2019/12/05
\brief      Spine skeleton component manager,I hate file header comments

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#pragma once

#include <unordered_map>

#include <glm/glm.hpp>

#include <UWUEngine/Component/Component.h>
#include <UWUEngine/Modules/SpineDataMod.h>
#include <UWUEngine/Graphics/GLSLShader.h>

namespace UWUEngine
{
  //Forward Declaration
  struct Vertex;
  class SpineSkeleton;

  //Manager
  class SpineSkeletonComp final : public Component<SpineSkeletonComp, SpineSkeleton>
  {
  public:
    SpineSkeletonComp(ISpace* p): Component<SpineSkeletonComp, SpineSkeleton>(p){}
    void InitObject(EntityID ID) override;
    void ShutdownObject(EntityID ID) override;

    void SetSkeleton(EntityID ID, SpineData& spineData);
    void SetSkeleton(EntityID ID, const char* name);
    SpineSkeleton& GetSkeleton(EntityID);

    const glm::mat4 GetScaleOffSet(EntityID ID);

    std::unordered_map<EntityID, SpineSkeleton>::iterator Begin();
    std::unordered_map<EntityID, SpineSkeleton>::iterator End();

  private:
    //Containers
    std::unordered_map<EntityID, SpineSkeleton> skeletons;
  };

  //Component
  class SpineSkeleton : public Instance<SpineSkeletonComp>
  {
  public:
    //Constructors
    explicit SpineSkeleton(SpineSkeletonComp&, SpineData&, EntityID);

    //Functions
    void Draw() const;
    void ChangeSkin(const char* skinName);

    //Getters
    [[nodiscard]] spSkeleton* GetSkeleton() const;
    [[nodiscard]] spSkeletonData* GetSkeletonData() const;

    friend SpineSkeletonComp;

  private:

    //Data Member
    spSkeleton* skeleton{};
    EntityID ID;
    float scaleOffset{ 1.0f };

    //Functions
    static void DrawMesh(
      std::vector<Vertex> vertices,
      std::vector<unsigned> indices,
      GLuint textureID
    );
  };
}
