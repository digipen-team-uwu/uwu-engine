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

#include <UWUEngine/Entity/EntityManager.h>
#include <UWUEngine/Entity/EntityVector.h>
#include <UWUEngine/Component/BaseComponent.h>

//Forward declaration
namespace Editors
{
  class Physics;
}

class PhysicsComponentManager : public BaseComponent<PhysicsComponentManager>
{
public:

  enum class BodyType
  {
    STATIC,
    DYNAMIC
  };

  PhysicsComponentManager() = default;
  ~PhysicsComponentManager() = default;
  void InitObject(EntityID ID) override;
  void Update() override;
  void ShutdownObject(EntityID ID) override {};

  static void SetBodyType(BodyType type, EntityID ID);
  static void SetOldTranslation(const glm::vec4& oldTranslation, EntityID ID);
  static void SetVelocity(const glm::vec4& velocity, EntityID ID);
  static void SetAcceleration(const glm::vec4& acceleration, EntityID ID);
  static void SetRotationalVelocity(const float rotationalVelocity, EntityID ID);
  static void SetInverseMass(const float inverseMass, EntityID ID);
  static void SetDrag(const glm::vec4& drag, EntityID ID);
  static void SetRestitution(float restitution, EntityID ID);

  static BodyType GetBodyType(EntityID ID);
  static const glm::vec4& GetAcceleration(EntityID ID);
  static const glm::vec4& GetVelocity(EntityID ID);
  static const glm::vec4& GetOldTranslation(EntityID ID);
  static float GetRotationalVelocity(EntityID ID);
  static const glm::vec4& GetDrag(EntityID ID);
  static float GetInverseMass(EntityID ID);
  static float GetRestitution(EntityID ID);

  static std::vector<glm::vec4>& GetDebugVelocities();

  static void Serialize(std::ofstream& stream, EntityID id, bool partial = false);

private:

  static EntityVector<BodyType> type_;

  // Previous position.  May be used for resolving collisions.
  static EntityVector<glm::vec4> oldTranslation_;

  // Acceleration = inverseMass * (sum of forces)
  static EntityVector<glm::vec4> acceleration_;

  // Velocity may be stored as a direction vector and speed scalar, instead.
  static EntityVector<glm::vec4> velocity_;

  // Rotational velocity (in radians).
  static EntityVector<float> rotationalVelocity_;

  // Drag to be applied to moving objects in order to slow them down.
  static EntityVector<glm::vec4> drag_;

  // Used when calculating acceleration due to forces.
  // Used when resolving collision between two dynamic objects.
  static EntityVector<float> inverseMass_;

  static EntityVector<float> restitution_;

  friend class Editors::Physics;
};
