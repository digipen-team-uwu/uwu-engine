/******************************************************************************/
/*!
\par        Project Umbra
\file       TransformComponentManager.h
\author     Chau Nguyen
\date       2019/09/13
\brief      Managing transform components

Copyright � 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#pragma once
#include <vector>
#include <glm/vec3.hpp>
#include <glm/matrix.hpp>
#include <UWUEngine/Component/EntityComp.h>
#include <UWUEngine/Component/Component.h>

namespace UWUEngine
{
  //Forward Declaration
  namespace Editors
  {
    class Transform;
  }
  class PhysicsSys;
  class TransformComp;

  class Transform
  {
  public:
    Transform(TransformComp& t, EntityID id);
    Transform(float& rotation, glm::vec4& translation, glm::vec3& scale);

  #pragma region Setter
    void SetTranslation(const glm::vec4& translation);
    void SetScale(const glm::vec3& scale);
    void SetRotation(const float& rotation);
  #pragma endregion

  #pragma region Getter
    const glm::vec4& GetTranslation() const;
    const glm::vec3& GetScale() const;
    const float& GetRotation() const;
  #pragma endregion 

  private:
    float& rotation_;
    glm::vec4& translation_;
    glm::vec3& scale_;
  };

  class TransformComp : public Component<TransformComp, Transform>
  {
  public:
    TransformComp(ISpace* space) : Component(space) {}
    ~TransformComp() = default;
    void ShutdownObject(EntityID ID) override {}
    void InitObject(EntityID ID) override;

    Transform operator[](EntityID index);

    Transform getTransform(EntityID index);

  #pragma region Getter
    const std::vector<glm::vec4>& GetArrayTranslation();
    const std::vector<float>& GetArrayRotation();
    const std::vector<glm::vec3>& GetArrayScale();
  #pragma endregion 

    glm::mat4 GetModelMatrix(EntityID ID);
    glm::mat4 GetSpineModelMatrix(EntityID ID);
    const glm::vec4& OffsetTranslation(EntityID ID, glm::vec3 const& offset);

  private:
    EntityVector<float> rotation_{ parent };
    EntityVector<glm::vec4> translation_{ parent };
    EntityVector<glm::vec3> scale_{ parent };

    friend class Transform;

    // don't know who added
    friend class Editors::Transform;
    friend class PhysicsSys;
  };
}
