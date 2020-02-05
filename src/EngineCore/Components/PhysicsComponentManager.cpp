/******************************************************************************/
/*!
\par        Project Umbra
\file       PhysicsComponentManager.cpp
\author     Chau Nguyen
\date       2019/09/13
\brief      Managing physics components

Copyright ☺ 2019 DigiPen, All rights reserved.

*/
/******************************************************************************/
#include <UWUEngine/Entity/EntityManager.h>
#include <UWUEngine/Component/PhysicsComponentManager.h>
#include <UWUEngine/Component/TransformComponentManager.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <UWUEngine/constants.h>
#include <UWUEngine/Serialization.h>
#include <UWUEngine/FrameRateController.h>
#include <magic_enum.hpp>

using namespace UWUEngine;
namespace goc = GameObjectConstants;

#pragma region Setter
void Physics::SetAcceleration(const glm::vec4& acceleration)
{
  acceleration_ = acceleration;
}

void Physics::SetVelocity(const glm::vec4& velocity)
{
  velocity_ = velocity;
}

void Physics::SetRotationalVelocity(const float& rotationalVelocity)
{
  rotationalVelocity_ = rotationalVelocity;
}

void Physics::SetBodyType(const BodyType& type)
{
  type_ = type;
}

void Physics::SetOldTranslation(const glm::vec4& oldTranslation)
{
  oldTranslation_ = oldTranslation;
}

void Physics::SetDrag(const glm::vec4& drag)
{
  drag_ = drag;
}

void Physics::SetRestitution(const float& restitution)
{
  restitution_ = restitution;
}

void Physics::SetInverseMass(const float& inverseMass)
{
  inverseMass_ = inverseMass;
}
#pragma endregion

#pragma region Getter
const BodyType& Physics::GetBodyType() const
{
  return type_;
}

const glm::vec4& Physics::GetAcceleration() const
{
  return acceleration_;
}

const glm::vec4& Physics::GetVelocity() const
{
  return velocity_;
}

const glm::vec4& Physics::GetOldTranslation() const
{
  return oldTranslation_;
}

const float& Physics::GetRotationalVelocity() const
{
  return rotationalVelocity_;
}

const glm::vec4& Physics::GetDrag() const
{
  return drag_;
}

const float& Physics::GetInverseMass() const
{
  return inverseMass_;
}

const float& Physics::GetRestitution() const
{
  return restitution_;
}
#pragma endregion

#pragma region Array Getter
const EntityVector<BodyType>& PhysicsComp::GetArrayBodyType() const
{
  return type_;
}

const EntityVector<glm::vec4>& PhysicsComp::GetArrayOldTranslation() const
{
  return oldTranslation_;
}

const EntityVector<glm::vec4>& PhysicsComp::GetArrayAcceleration() const
{
  return acceleration_;
}

const EntityVector<glm::vec4>& PhysicsComp::GetArrayDrag() const
{
  return drag_;
}

const EntityVector<glm::vec4>& PhysicsComp::GetArrayVelocity() const
{
  return velocity_;
}

const EntityVector<float>& PhysicsComp::GetArrayRotationalVelocity() const
{
  return rotationalVelocity_;
}

const EntityVector<float>& PhysicsComp::GetArrayInverseMass() const
{
  return inverseMass_;
}

const EntityVector<float>& PhysicsComp::GetArrayRestitution() const
{
  return restitution_;
}
#pragma endregion 

Physics PhysicsComp::operator[](EntityID ID)
{
  return Physics(type_[ID], oldTranslation_[ID], acceleration_[ID], velocity_[ID], drag_[ID],
    rotationalVelocity_[ID], inverseMass_[ID], restitution_[ID]);
}

Physics PhysicsComp::getPhysics(EntityID ID)
{
  return Physics(type_[ID], oldTranslation_[ID], acceleration_[ID], velocity_[ID], drag_[ID], 
    rotationalVelocity_[ID], inverseMass_[ID], restitution_[ID]);
}


void PhysicsComp::InitObject(EntityID ID)
{
  type_[ID] = BodyType::STATIC;
  rotationalVelocity_[ID] = 0.0f;
  drag_[ID] = { 0, 0, 0, 0 };
  velocity_[ID] = glm::vec4(0.0f);
  acceleration_[ID] = glm::vec4(0.0f);
  inverseMass_[ID] = 0.0f;
  restitution_[ID] = 1.0f;
}

void PhysicsComp::Update()
{
  //TODO: Need a way to access transform manager to update physics correctly
  std::vector<EntityID> ids = EntityManager::GetIDs();
  auto it = ids.begin();

  oldTranslation_.operator std::vector<glm::vec4, std::allocator<glm::vec4>>& ().swap(TransformComponentManager::translation_);

  while (it != ids.end())
  {
    if (TransformComponentManager::IsActive(*it) && IsActive(*it))
    {
      float dt = FrameRateController::GetDeltaTime<float>();
      const glm::vec4 pos = oldTranslation_[*it];
      const glm::vec4 vel = velocity_[*it];
      const glm::vec4 acl = acceleration_[*it];
      float invMass = inverseMass_[*it];

      oldTranslation_[*it] = pos;
      glm::vec4 newVel = (vel + (acl * invMass) * dt) * (glm::vec4{ 1, 1, 1, 0 } -drag_[*it] * dt);
      glm::vec4 newPos = pos + newVel * dt;
      TransformComponentManager::SetTranslation(newPos, *it);
      velocity_[*it] = newVel;
      TransformComponentManager::SetRotation(TransformComponentManager::GetRotation(*it) + rotationalVelocity_[*it] * dt, *it);
    }
    else
    {
      TransformComponentManager::SetTranslation(oldTranslation_[*it], *it);
    }
    ++it;
  }

  /*static int frameoffset;
  ++frameoffset;
  if (frameoffset % 3 == 0)
  {
    auto& rot = const_cast<std::vector<float>&>(TransformComponentManager::GetArrayRotation());
    EntityVectorManager::QuickSortBy(rot);
  }*/
}

// Below code written by Michael Rollosson Halbhuber
void PhysicsComp::Serialize(std::ofstream& stream, EntityID id, bool partial)
{
  // Check if the given ID has an active physics component
  if (PhysicsComp::IsActive(id))
  {
    // Open a "physics" JSON object
    stream << "\"physics\" :\n";
    stream << Tabs::TWO <<  "{\n";

    // Serialize body type
    stream << Tabs::THREE << R"("type" : ")" << magic_enum::enum_name(type_[id]) << '"';
    stream << ",\n";

    // Print the velocity
    SerializeVec4(stream, "velocity", velocity_[id]);
    stream << ",\n";

    // Print the acceleration
    SerializeVec4(stream, "acceleration", acceleration_[id]);
    stream << ",\n";

    // Print the rotational velocity
    stream << Tabs::THREE << "\"rotational velocity\" : " << rotationalVelocity_[id] << ",\n";

    if (!partial)
    {
      // Print the drag
      SerializeVec4(stream, "drag", drag_[id]);
      stream << ",\n";

      // Print the Inverse Mass
      stream << Tabs::THREE << "\"inverse mass\" : " << inverseMass_[id] << "\n";
    }
    else
    {
      // Print to avoid json errors
      // Doesn't need to be used for anything else, but nobody is stopping you from doing so
      stream << Tabs::THREE << "\"partial\" : true";
    }
    // Close the physics object
    stream << "}";
  }
}