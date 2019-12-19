/******************************************************************************/
/*!
\par        Project Umbra
\file       ColliderComponentManager.cpp
\author     Yi Qian
\date       2019/12/05
\brief      Collider component manager,I hate file header comments

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#define GLM_FORCE_SWIZZLE

#include <UWUEngine/Component/ColliderComponentManager.h>

template<>
size_t RegisterComponentHelper<ColliderComponentManager>::RegisterComponentHelper_ID = EntityManager::AddComponent<ColliderComponentManager>(ComponentUpdateOrder::Collider);

#include <UWUEngine/Component/BehaviorComponentManager.h>
#include <UWUEngine/Component/TransformComponentManager.h>
#include <UWUEngine/Component/PhysicsComponentManager.h>
#include <UWUEngine/Physics/Colliders/ColliderCircle.h>
#include <UWUEngine/Physics/Colliders/ColliderLine.h>
#include <UWUEngine/Physics/Colliders/ColliderPoint.h>
#include <UWUEngine/Physics/Colliders/ColliderPolygon.h>

#include <UWUEngine/Debugs/TraceLogger.h>

std::unordered_map<EntityID, Collider*> ColliderComponentManager::_collider;

void DispatchCollisionEvent(CollisionInfo const&);

ColliderComponentManager::~ColliderComponentManager()
{
  for (auto& i : _collider)
  {
    delete i.second;
  }
  _collider.clear();
}

void ColliderComponentManager::Update()
{
  //Detection and Resolution
  for (auto i = _collider.begin(); i != _collider.end(); ++i)
  {
    PhysicsComponentManager::BodyType type1 = PhysicsComponentManager::GetBodyType(i->first);
    for (auto j = std::next(i); j != _collider.end(); ++j)
    {
      //Ignore STATIC - STATIC collision
      PhysicsComponentManager::BodyType type2 = PhysicsComponentManager::GetBodyType(j->first);
      if (type1 == PhysicsComponentManager::BodyType::STATIC && type2 == PhysicsComponentManager::BodyType::STATIC)
      {
        continue;
      }

      //Collision Detection
      const CollisionInfo info = i->second->IsColliding(*j->second);

      //TODO: event system

      if (info.depth != 0)
      {
        DispatchCollisionEvent(info);
        ResolveCollision(info);
      }
    }
  }
}

void ColliderComponentManager::InitObject(EntityID ID)
{
  PhysicsComponentManager::Activate(ID);
}

void ColliderComponentManager::ShutdownObject(EntityID ID)
{
  delete GetCollider(ID);
  _collider.erase(ID);
}

void ColliderComponentManager::SetCollider(EntityID ID, Collider const* collider)
{
  auto currCollider = _collider.find(ID);
  if (currCollider != _collider.end())
  {
    delete currCollider->second;
    _collider.erase(ID);
  }
  Collider* newCollider = collider->Clone();
  newCollider->ID = ID;
  _collider.insert({ ID, newCollider });
}

void ColliderComponentManager::SetPointCollider(EntityID ID, glm::vec2 position)
{
  _collider.insert({ ID, static_cast<Collider*>(new ColliderPoint(ID, position)) });
}

void ColliderComponentManager::SetLineCollider(EntityID ID, glm::vec2 p1, glm::vec2 p2)
{
  _collider.insert({ ID, static_cast<Collider*>(new ColliderLine(ID, p1, p2)) });
}

void ColliderComponentManager::SetCircularCollider(EntityID ID, glm::vec2 center, float radius)
{
  _collider.insert({ ID, static_cast<Collider*>(new ColliderCircle(ID, center, radius)) });
}

void ColliderComponentManager::SetRectangleCollider(EntityID ID)
{
  _collider.insert({ ID, static_cast<Collider*>(new ColliderPolygon(ID)) });
}

void ColliderComponentManager::SetPolygonCollider(EntityID ID)
{
  //insert a polygon collider with default center (0, 0)
  _collider.insert({ ID, static_cast<Collider*>(new ColliderPolygon(ID, {0,0})) });
}

Collider const* ColliderComponentManager::GetCollider(EntityID ID)
{
  return _collider.find(ID)->second;
}

void ColliderComponentManager::Serialize(std::ofstream& stream, EntityID id)
{
  if (IsActive(id))
  {
    //TODO:serialize collider
    GetCollider(id)->Serialize(stream);
  }
}

std::unordered_map<EntityID, Collider*>::const_iterator ColliderComponentManager::begin()
{
  return _collider.cbegin();
}

std::unordered_map<EntityID, Collider*>::const_iterator ColliderComponentManager::end()
{
  return _collider.cend();
}

void ColliderComponentManager::ResolveCollision(CollisionInfo const& info)
{
  // 1.Snap Them off
  glm::vec4 obj1trans = TransformComponentManager::GetTranslation(info.obj1);
  glm::vec4 obj2trans = TransformComponentManager::GetTranslation(info.obj2);

  const float proj1 = ProjectPoint(obj1trans.xy, info.direction);
  const float proj2 = ProjectPoint(obj2trans.xy, info.direction);

  glm::vec2 direction = info.direction * abs(info.depth);
  direction = proj1 > proj2 ? direction : -direction;

  const float mass1 = PhysicsComponentManager::GetInverseMass(info.obj1);
  const float mass2 = PhysicsComponentManager::GetInverseMass(info.obj2);
  const float massRat = mass1 / (mass1 + mass2);

  const glm::vec2 dirObject1 = direction * massRat;
  const glm::vec2 dirObject2 = direction - dirObject1;

  obj1trans.xy += dirObject1;
  obj2trans.xy -= dirObject2;

  TransformComponentManager::SetTranslation(obj1trans, info.obj1);
  TransformComponentManager::SetTranslation(obj2trans, info.obj2);

  // 2. Resolve velocity
  glm::vec2 vel1 = PhysicsComponentManager::GetVelocity(info.obj1);
  glm::vec2 vel2 = PhysicsComponentManager::GetVelocity(info.obj2);

  vel1 -= info.direction * glm::dot(vel1, info.direction);
  vel2 -= info.direction * glm::dot(vel2, info.direction);

  PhysicsComponentManager::SetVelocity(glm::vec4(vel1, 0, 0), info.obj1);
  PhysicsComponentManager::SetVelocity(glm::vec4(vel2, 0, 0), info.obj2);
}

void DispatchCollisionEvent(CollisionInfo const& info)
{
  //Behavioral resolution
  //TODO: event system

  switch (EntityManager::GetType(info.obj1))
  {
  case Type::Player:
    BehaviorComponentManager::GetBehavior<EntityManager::Player>(info.obj1)->OnCollide(info);
    break;
  case Type::Fang_:
    BehaviorComponentManager::GetBehavior<EntityManager::Fang_>(info.obj1)->OnCollide(info);
    break;
  case Type::Perception:
    BehaviorComponentManager::GetBehavior<EntityManager::Perception>(info.obj1)->OnCollide(info);
    break;
  default:;
  }

  switch (EntityManager::GetType(info.obj2))
  {
  case Type::Player:
    BehaviorComponentManager::GetBehavior<EntityManager::Player>(info.obj2)->OnCollide(info);
    break;
  case Type::Fang_:
    BehaviorComponentManager::GetBehavior<EntityManager::Fang_>(info.obj2)->OnCollide(info);
    break;
  case Type::Perception:
    BehaviorComponentManager::GetBehavior<EntityManager::Perception>(info.obj2)->OnCollide(info);
    break;
  case Type::Solid:
  default:;
  }
}
