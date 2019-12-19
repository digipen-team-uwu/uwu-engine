/******************************************************************************/
  /*!
  \par        Project Umbra
  \file       Dynamic.cpp
  \author     Hadi Alhussieni
  \date       2019/12/05
  \brief      Implementation for behaviors for player's HUD objects

  Copyright � 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#include <UWUEngine/Behaviors/HUDBehaviors.h>
#include <UWUEngine/Component/ParentChildComponentManager.h>
#include <UWUEngine/Component/TransformComponentManager.h>
#include <UWUEngine/Component/TextureComponentManager.h>
#include <UWUEngine/UI/UIManager.h>
#include <UWUEngine/Engine.h>

void Behavior<EntityManager::Type::HUDHealth>::Render()
{
  glm::vec4 offset = {};
  offset.x = 0.f;
  for (size_t i = 0; i < 3; ++i)
  {
    if (health <= i)
      TextureComponentManager::SetCurrentTexture(GetID(), 1);
    else
      TextureComponentManager::SetCurrentTexture(GetID(), 0);

      UIManager::PushElement(0, TransformComponentManager::GetTranslation(GetID()) + offset, TransformComponentManager::GetScale(GetID()),
        TextureComponentManager::GetColor(GetID()), { 0, 0 },
       TextureComponentManager::GetDimensions(GetID()), TextureAtlaser::GetAtlasUV(GetID()),
      TextureAtlaser::GetAtlasScale(GetID()), TextureAtlaser::GetAtlasLayers(GetID()));
      offset.x += 70.f;
  }
}

void Behavior<EntityManager::Type::HUDEnergy>::Update()
{
  EntityID particles = ParentChildComponentManager::GetChildren(GetID())[0];
  /* static Timer timer(2);
  if (timer.Finished())
  {
    EntityCacher::UpdateCachedBehavior("Energy");
    EntityCacher::InstantiateCachedBehavior(particles, "Energy");
  }*/
  TransformComponentManager::SetTranslation(TransformComponentManager::GetTranslation(GetID()) + glm::vec4{ 0, 20, 0, 0 }, particles);
  auto& event = BehaviorComponentManager::GetBehavior<EntityManager::Type::ParticleEmitter>(particles)->GetEvent();
  event.scale.scaleRate = energy / 50.f;
  if (energy != 0)
  {
    event.emissionRate.SetRange(1.f / (energy * 1.5) , 1.f / (energy * 1.5) * 1.2);
    event.particlesPerEmission = 1;
  }
  else
  {
    event.particlesPerEmission = 0;
  }
}
Behavior<EntityManager::Type::HUDEnergy>::Behavior(EntityID id) : BaseBehavior(id), energy(0)
{
  ParentChildComponentManager::Activate(id);
  EntityID particles = EntityFactory::CreateObject(EntityManager::Type::ParticleEmitter);
  ParentChildComponentManager::AddChild(id, particles);
  EntityCacher::InstantiateCachedBehavior(particles, "Energy");
  EntityManager::SetClearImmunity(particles, true);
  EntityManager::SetDontSerialize(particles, true);
}

void Behavior<EntityManager::Type::HUDEnergy>::Render()
{
    UIManager::PushElement(0, TransformComponentManager::GetTranslation(GetID()), TransformComponentManager::GetScale(GetID()),
      TextureComponentManager::GetColor(GetID()), { 0, 0 },
      TextureComponentManager::GetDimensions(GetID()), TextureAtlaser::GetAtlasUV(GetID()),
      TextureAtlaser::GetAtlasScale(GetID()), TextureAtlaser::GetAtlasLayers(GetID()));
}