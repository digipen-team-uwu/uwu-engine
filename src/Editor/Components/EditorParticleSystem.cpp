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

#include <UWUEngine/Editor/Components/EditorParticleSystem.h>
#include <UWUEngine/Behaviors/ParticleSystem.h>
#include <UWUEngine/Entity/EntityManager.h>
#include <imgui.h>

Editors::ParticleEmitter::ParticleEmitter(const std::string& name):
Component(name)
{
}

void Editors::ParticleEmitter::CheckActive(EntityID id)
{
  isActive = EntityManager::GetType(id) == EntityManager::Type::ParticleEmitter && BehaviorComponentManager::IsActive(id);
}

void Editors::ParticleEmitter::UpdateComponent(EntityID id)
{
  auto &emitter = BehaviorComponentManager::GetBehavior<EntityManager::Type::ParticleEmitter>(id)->GetEvent();
  color.UpdateElement(&emitter.color.color);
  endColor.UpdateElement(&emitter.color.endColor);
  colorRate.UpdateElement(&emitter.color.colorRate);
  scale.UpdateElement(&emitter.scale.scale);
  endScale.UpdateElement(&emitter.scale.endScale);
  scaleRate.UpdateElement(&emitter.scale.scaleRate);
}

void Editors::ParticleEmitter::UpdateUI()
{
  color.UpdateUI();
  endColor.UpdateUI();
  colorRate.UpdateUI();
  scale.UpdateUI();
  endScale.UpdateUI();
  scaleRate.UpdateUI();
}
