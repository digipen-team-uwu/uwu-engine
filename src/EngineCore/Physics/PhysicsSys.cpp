#include <UWUEngine/Systems/PhysicsSys.h>
#include <UWUEngine/Systems/LogSys.h>
#include <UWUEngine/Systems/CompSpaceSys.h>
#include <UWUEngine/Systems/FrameLimiterSys.h>

using namespace UWUEngine;

PhysicsSys::PhysicsSys(ISpace* p):
System(p)
{
  
}

void PhysicsSys::Update()
{
  auto& compSys = Get<CompSpaceSys>();

  UpdateSpace(compSys.space_ui.Get<EntityComp>(), compSys.space_ui.Get<TransformComp>(), compSys.space_ui.Get<PhysicsComp>());
  UpdateSpace(compSys.space_gameplay.Get<EntityComp>(), compSys.space_gameplay.Get<TransformComp>(), compSys.space_gameplay.Get<PhysicsComp>());
  UpdateSpace(compSys.space_particle.Get<EntityComp>(), compSys.space_particle.Get<TransformComp>(), compSys.space_particle.Get<PhysicsComp>());
}

void PhysicsSys::UpdateSpace(EntityComp& entityComp, TransformComp& transformComp, PhysicsComp& physicsComp)
{
  auto& frameSys = Get<FrameLimiterSys>();

  size_t entityCount = entityComp.GetIDCount();

  physicsComp.oldTranslation_.Swap(transformComp.translation_);

  for (auto i : entityComp.GetIDs())
  {
    float dt = frameSys.GetDeltaTime<float>();

    const glm::vec4& pos = physicsComp.oldTranslation_[i];
    const glm::vec4& vel = physicsComp.velocity_[i];
    const glm::vec4& acl = physicsComp.acceleration_[i];
    const glm::vec4& drag = physicsComp.drag_[i];
    const float& invMass = physicsComp.inverseMass_[i];

    glm::vec4 newVel = (vel + (acl * invMass) * dt) * (glm::vec4{ 1, 1, 1, 0 } - drag * dt);
    glm::vec4 newPos = pos + newVel * dt;

    transformComp.translation_[i] = newPos;
    physicsComp.velocity_[i] = newVel;
    transformComp.rotation_[i] += physicsComp.rotationalVelocity_[i];
  }
}
