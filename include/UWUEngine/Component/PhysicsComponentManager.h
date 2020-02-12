/******************************************************************************/
/*!
\par        Project Umbra
\file       PhysicsComponentManager.h
\author     Chau Nguyen
\date       2019/09/13
\brief      Managing physics components

Copyright � 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#pragma once
#include <vector>
#include <glm/vec3.hpp>
#include <glm/matrix.hpp>

#include <UWUEngine/Entity/EntitySys.h>
#include <UWUEngine/Entity/EntityVector.h>
#include <UWUEngine/Component/Component.h>


namespace UWUEngine
{
  namespace Editors
  {
    class Physics;
  };

  enum class BodyType
  {
    STATIC,
    DYNAMIC
  };

  class Physics
  {
  public:
    Physics(BodyType& type, glm::vec4& oldTranslation, glm::vec4& acceleration, glm::vec4& velocity, glm::vec4& drag, float& rotationalVelocity, float& inverseMass, float& restitution)
      : type_(type), oldTranslation_(oldTranslation), acceleration_(acceleration), velocity_(velocity), drag_(drag), rotationalVelocity_(rotationalVelocity), inverseMass_(inverseMass), restitution_(restitution)
    {}

#pragma region Setter
    void SetBodyType(const BodyType& type);
    void SetOldTranslation(const glm::vec4& oldTranslation);
    void SetAcceleration(const glm::vec4& acceleration);
    void SetVelocity(const glm::vec4& velocity);
    void SetDrag(const glm::vec4& drag);
    void SetRotationalVelocity(const float& rotationalVelocity);
    void SetInverseMass(const float& inverseMass);
    void SetRestitution(const float& restitution);
#pragma endregion

#pragma region Getter
    const BodyType& GetBodyType() const;
    const glm::vec4& GetOldTranslation() const;
    const glm::vec4& GetAcceleration() const;
    const glm::vec4& GetVelocity() const;
    const glm::vec4& GetDrag() const;
    const float& GetRotationalVelocity() const;
    const float& GetInverseMass() const;
    const float& GetRestitution() const;
#pragma endregion 
  private:
    BodyType& type_;
    glm::vec4& oldTranslation_;
    glm::vec4& acceleration_;
    glm::vec4& velocity_;
    glm::vec4& drag_;
    float& rotationalVelocity_;
    float& inverseMass_;
    float& restitution_;
  };

  class PhysicsComp : public Component<PhysicsComp, Physics>
  {
  public:
    PhysicsComp() = default;
    ~PhysicsComp() = default;
    void InitObject(EntityID ID) override;
    void Update() override;
    void ShutDownObject(EntityID ID) override {};

    Physics operator[](EntityID ID);
    Physics getPhysics(EntityID ID);

#pragma region Getter
    const EntityVector<BodyType>& GetArrayBodyType() const;
    const EntityVector<glm::vec4>& GetArrayOldTranslation() const;
    const EntityVector<glm::vec4>& GetArrayAcceleration() const;
    const EntityVector<glm::vec4>& GetArrayVelocity() const;
    const EntityVector<glm::vec4>& GetArrayDrag() const;
    const EntityVector<float>& GetArrayRotationalVelocity() const;
    const EntityVector<float>& GetArrayInverseMass() const;
    const EntityVector<float>& GetArrayRestitution() const;
#pragma endregion

    void Serialize(::std::ofstream& stream, EntityID id, bool partial);

  private:
    EntityVector<BodyType> type_;
    EntityVector<glm::vec4> oldTranslation_;
    EntityVector<glm::vec4> acceleration_;
    EntityVector<glm::vec4> velocity_;
    EntityVector<glm::vec4> drag_;
    EntityVector<float> rotationalVelocity_;
    EntityVector<float> inverseMass_;
    EntityVector<float> restitution_;
    friend class Editors::Physics;
  };
}


