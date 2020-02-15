/******************************************************************************/
/*!
\par        Project Umbra
\file       ColliderComp.cpp
\author     Yi Qian
\date       2019/12/05
\brief      Collider component manager,I hate file header comments

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#define GLM_FORCE_SWIZZLE
#define EventSystemEnabled

#include <UWUEngine/Component/ColliderComp.h>


//#include <UWUEngine/Component/BehaviorComp.h>
#include <UWUEngine/Component/TransformComp.h>
#include <UWUEngine/Component/PhysicsComp.h>
#include <UWUEngine/Physics/Colliders/ColliderCircle.h>
#include <UWUEngine/Physics/Colliders/ColliderLine.h>
#include <UWUEngine/Physics/Colliders/ColliderPoint.h>
#include <UWUEngine/Physics/Colliders/ColliderPolygon.h>

#include <UWUEngine/Systems/EventSys.h>
#include <UWUEngine/Systems/LogSys.h>

void DispatchCollisionEvent(UWUEngine::Event<EventType::Collision> const&);

namespace UWUEngine
{
ColliderComp::ColliderComp(ISpace* space) : Component(space)
{
  //EventSystem::Register(listener_);
}

ColliderComp::~ColliderComp()
{
  for (auto& i : _collider)
  {
    delete i.second;
  }
  _collider.clear();
  //EventSystem::UnRegister(listener_);
}

void ColliderComp::InitObject(EntityID ID)
{
  _collider.insert({ID, nullptr});
}

void ColliderComp::ShutdownObject(EntityID ID)
{
  const Collider* collider = GetCollider(ID);
  if (collider)
  {
    delete GetCollider(ID);
  }
  
  _collider.erase(ID);
}

void ColliderComp::SetCollider(EntityID ID, Collider const* collider)
{
  auto currCollider = _collider.find(ID);
  if (currCollider != _collider.end())
  {
    delete currCollider->second;
    _collider.erase(ID);
  }
  Collider* newCollider = collider->Clone();
  newCollider->ID = ID;
  _collider.insert_or_assign(ID, newCollider);
}

void ColliderComp::SetPointCollider(EntityID ID, glm::vec2 position)
{
  _collider.insert_or_assign(ID, static_cast<Collider*>(new ColliderPoint(*this, ID, position)));
}

void ColliderComp::SetLineCollider(EntityID ID, glm::vec2 p1, glm::vec2 p2)
{
  _collider.insert_or_assign(ID, static_cast<Collider*>(new ColliderLine(*this, ID, p1, p2)));
}

void ColliderComp::SetCircularCollider(EntityID ID, glm::vec2 center, float radius)
{
  _collider.insert_or_assign(ID, static_cast<Collider*>(new ColliderCircle(*this, ID, center, radius)));
}

void ColliderComp::SetRectangleCollider(EntityID ID)
{
  _collider.insert_or_assign(ID, static_cast<Collider*>(new ColliderPolygon(*this, ID)));
}

void ColliderComp::SetPolygonCollider(EntityID ID)
{
  //insert a polygon collider with default center (0, 0)
  _collider.insert_or_assign(ID, static_cast<Collider*>(new ColliderPolygon(*this, ID, {0,0})));
}

Collider const* ColliderComp::GetCollider(EntityID ID)
{
  const auto& collider = _collider.find(ID);
  if (collider == _collider.end())
  {
    return nullptr;
  }
  return collider->second;
}

void ColliderComp::Serialize(std::ofstream& stream, EntityID id)
{
  //TODO:serialize collider
  GetCollider(id)->Serialize(stream);
}

std::unordered_map<EntityID, Collider*>::const_iterator ColliderComp::begin()
{
  return _collider.cbegin();
}

std::unordered_map<EntityID, Collider*>::const_iterator ColliderComp::end()
{
  return _collider.cend();
}

void ColliderComp::ResolveCollision(Event<EventType::Collision> const& info)
{
  // 1.Snap Them off
  glm::vec4 obj1trans = Get<TransformComp>().getTransform(info.obj1).GetTranslation();
  glm::vec4 obj2trans = Get<TransformComp>().getTransform(info.obj2).GetTranslation();

  const float proj1 = ProjectPoint(obj1trans.xy(), info.direction);
  const float proj2 = ProjectPoint(obj2trans.xy(), info.direction);

  glm::vec2 direction = info.direction * std::abs(info.depth);
  direction = proj1 > proj2 ? direction : -direction;

  const float mass1 = Get<PhysicsComp>().getPhysics(info.obj1).GetInverseMass();
  const float mass2 = Get<PhysicsComp>().getPhysics(info.obj2).GetInverseMass();
  const float massRat = mass1 / (mass1 + mass2);

  const glm::vec2 dirObject1 = direction * massRat;
  const glm::vec2 dirObject2 = direction - dirObject1;

  obj1trans.x += dirObject1.x;
  obj1trans.y += dirObject1.y;
  obj2trans.x -= dirObject2.x;
  obj2trans.y -= dirObject2.y;

  Get<TransformComp>().getTransform(info.obj1).SetTranslation(obj1trans);
  Get<TransformComp>().getTransform(info.obj2).SetTranslation(obj2trans);

  // 2. Resolve velocity
  glm::vec2 vel1 = Get<PhysicsComp>().getPhysics(info.obj1).GetVelocity();
  glm::vec2 vel2 = Get<PhysicsComp>().getPhysics(info.obj2).GetVelocity();

  vel1 -= info.direction * glm::dot(vel1, info.direction);
  vel2 -= info.direction * glm::dot(vel2, info.direction);

  Get<PhysicsComp>().getPhysics(info.obj1).SetVelocity(glm::vec4(vel1, 0, 0));
  Get<PhysicsComp>().getPhysics(info.obj2).SetVelocity(glm::vec4(vel1, 0, 0));
}

}
