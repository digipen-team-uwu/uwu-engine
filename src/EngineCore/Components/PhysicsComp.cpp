/******************************************************************************/
/*!
\par        Project Umbra
\file       PhysicsComponentManager.cpp
\author     Chau Nguyen
\date       2019/09/13
\brief      Managing physics components

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#include <UWUEngine/Component/PhysicsComp.h>
#include <UWUEngine/Component/TransformComp.h>
#include <UWUEngine/constants.h>

#include <glm/gtc/matrix_transform.hpp>

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


PhysicsComp::PhysicsComp(ISpace* p):
Component<UWUEngine::PhysicsComp, UWUEngine::Physics>(p)
{
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
