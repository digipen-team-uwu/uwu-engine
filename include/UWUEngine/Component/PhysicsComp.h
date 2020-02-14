/******************************************************************************/
/*!
\par        Project Umbra
\file       PhysicsComponentManager.h
\author     Chau Nguyen
\date       2019/09/13
\brief      Managing physics components

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#pragma once
#include <fstream>
#include <glm/vec3.hpp>
#include <glm/matrix.hpp>

#include <UWUEngine/Component/EntityComp.h>
#include <UWUEngine/Component/Component.h>


namespace UWUEngine
{
  //Forward Declaration
  class PhysicsSys;

  namespace Editors
  {
    class Physics;
  };

  enum class BodyType
  {
    STATIC,
    DYNAMIC
  };

  class Physics : NonCopyable
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
    PhysicsComp(ISpace* p);
    ~PhysicsComp() = default;

    void InitObject(EntityID ID) override;
    void ShutdownObject(EntityID ID) override{}

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
    EntityVector<BodyType> type_{parent};
    EntityVector<glm::vec4> oldTranslation_{parent};
    EntityVector<glm::vec4> acceleration_{parent};
    EntityVector<glm::vec4> velocity_{parent};
    EntityVector<glm::vec4> drag_{parent};
    EntityVector<float> rotationalVelocity_{parent};
    EntityVector<float> inverseMass_{parent};
    EntityVector<float> restitution_{parent};

    friend class Editors::Physics;
    friend class PhysicsSys;
  };
}


