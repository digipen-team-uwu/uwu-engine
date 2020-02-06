/******************************************************************************/
/*!
\par        Project Umbra
\file       SpineSkeletonComponentManager.h
\author     Yi Qian
\date       2019/12/05
\brief      Spine skeleton component manager,I hate file header comments

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#pragma once

#include <unordered_map>

#include <UWUEngine/Component/Component.h>
#include <UWUEngine/Graphics/SpineAnimation/SpineDataManager.h>
#include <UWUEngine/Graphics/Shader/glslshader.h>

#ifdef _DEBUG
#include <UWUEngine/Physics/Colliders/ColliderPolygon.h>
#endif

namespace UWUEngine
{
  //Forward Declaration
  struct Vertex;
  class SpineSkeletonComp;

  //Component
  class SpineSkeleton
  {
  public:
    //Constructors
    explicit SpineSkeleton(SpineData&, EntityID);

    //Functions
    void Draw() const;
    void ChangeSkin(const char* skinName);

    //Getters
    [[nodiscard]] spSkeleton* GetSkeleton() const;
    [[nodiscard]] spSkeletonData* GetSkeletonData() const;

    friend SpineSkeletonComp;

#ifdef _DEBUG
    friend ColliderPolygon;
#endif


  private:

    //Data Member
    spSkeleton* skeleton{};
    EntityID ID;
    float scaleOffset{ 1.0f };

    //Static Data Member
    GLSLShader shader_;

    //Functions
    void DrawMesh(
      std::vector<Vertex> vertices,
      std::vector<unsigned> indices,
      GLuint textureID
    );
  };

  //Manager
  class SpineSkeletonComp : public Component<SpineSkeletonComp>
  {
  public:
    SpineSkeletonComp() = default;
    void Update() override;
    void InitObject(EntityID ID) override;
    void ShutdownObject(EntityID ID) override;
    void Render(EntityID ID);

    void SetSkeleton(EntityID ID, SpineData& spineData);
    void SetSkeleton(EntityID ID, const char* name);
    SpineSkeleton& GetSkeleton(EntityID);

    const glm::mat4 GetScaleOffSet(EntityID ID);

  private:
    //Containers
    std::unordered_map<EntityID, SpineSkeleton> skeletons;
  };
}
