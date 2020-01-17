/******************************************************************************/
/*!
\par        Project Umbra
\file       EditorPhysics.cpp
\author     Yi Qian
\date       2020/01/01
\brief      Physics Editor

Copyright © 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#include <UWUEngine/Editor/Components/EditorPhysics.h>
#include <UWUEngine/Component/PhysicsComponentManager.h>

#include <imgui.h>

Editors::Physics::Physics(const std::string& name):
Component(name)
{
}

Editors::Physics::~Physics()
= default;

void Editors::Physics::CheckActive(EntityID id)
{
  isActive = PhysicsComponentManager::IsActive(id);
}

void Editors::Physics::UpdateComponent(EntityID id)
{
  inverseMass.UpdateElement(&PhysicsComponentManager::inverseMass_[id]);
  velocity.UpdateElement(reinterpret_cast<glm::vec3*>(&PhysicsComponentManager::velocity_[id]));
  acceleration.UpdateElement(reinterpret_cast<glm::vec3*>(&PhysicsComponentManager::acceleration_[id]));
  drag.UpdateElement(reinterpret_cast<glm::vec3*>(&PhysicsComponentManager::drag_[id]));
  rotationalVel.UpdateElement(&PhysicsComponentManager::rotationalVelocity_[id]);
}

void Editors::Physics::UpdateUI()
{
  inverseMass.UpdateUI();
  velocity.UpdateUI();
  acceleration.UpdateUI();
  drag.UpdateUI();
  rotationalVel.UpdateUI();
}
