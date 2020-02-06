/******************************************************************************/
  /*!
  \par        Project Umbra
  \file       DynamicCamera.cpp
  \author     Hadi Alhussieni
  \date       2019/12/05
  \brief      Implementation for a camera that follows a target within specific bounds

  Copyright � 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#include <UWUEngine/Behaviors/DynamicCamera.h>
#include <UWUEngine/Graphics/CameraSys.h>
#include <UWUEngine/FrameLimiterSys.h>
#include <UWUEngine/Component/TransformComponentManager.h>
#include <UWUEngine/Serialization.h>
#include <limits>

namespace UWUEngine
{

DynamicCamera::DynamicCamera(ISpace* p) : System(p) {}

void DynamicCamera::Update()
{
  if (!IsActive)
  {
    return;
  }
  glm::vec4 newPos = glm::vec4(Get<CameraSys>().GetPosition(), 1);
  //check if camera pos is within target bounds

  /*static EntityID debug = EntityFactory::CreateObject(EntityManager::Type::Cyclone);
  static EntityID debug2 = EntityFactory::CreateObject(EntityManager::Type::Cyclone);
  TransformComponentManager::SetScale({ 100, 100, 0 }, debug);
  TransformComponentManager::SetTranslation(glm::vec4(glm::vec2(newPos), 15, 1), debug);
  EntityManager::SetClearImmunity(debug, true);*/
  /*
  if (!InAnyBounds(position))
  {
    glm::vec4 direction = glm::normalize(newPos - position);
    glm::vec2 closestPoint = GetClosestPointOnBounds(position, direction);
    if (closestPoint == psc::UNUSED_VEC2)
    {
      return;
    }

    TransformComponentManager::SetScale({ 100, 100, 0 }, debug2);
    TransformComponentManager::SetTranslation(glm::vec4(closestPoint, 15, 1), debug2);
    EntityManager::SetClearImmunity(debug2, true);

      //TODO: interpolate between old target position and new target position to smooth out camera further
    Camera::SetCameraPosition(glm::mix(glm::vec2(newPos), closestPoint, followSpeed * FrameRateController::GetDeltaTime<float>()));
  } */
  if (newPos.x > position.x + inoffset.x + inwidth / 2
      || newPos.x < position.x + inoffset.x - inwidth / 2
      || newPos.y > position.y + inoffset.y + inheight / 2
      || newPos.y < position.y + inoffset.y - inheight / 2)
  {
    glm::vec4 direction = glm::normalize((position + glm::vec4(inoffset, 0, 0)) - newPos);
    //raycast camera pos onto AABB bounds, find minimum T
    glm::vec4 invDir = 1.f / direction;
    float min = ((invDir.x < 0 ? position.x + inoffset.x + inwidth / 2 : position.x + inoffset.x - inwidth / 2) - newPos.x) * invDir.x;
    float ymin = ((invDir.y < 0 ? position.y + inoffset.y + inheight / 2 : position.y + inoffset.y - inheight / 2) - newPos.y) * invDir.y;
    if (ymin > min)
      min = ymin;

    //TransformComponentManager::SetScale({ 100, 100, 0 }, debug2);
    //TransformComponentManager::SetTranslation(glm::vec4(glm::vec2(position), 15, 0), debug2);

    glm::vec4 closest = (newPos + direction * min);
    if (!InAnyBounds(position))
    {
      glm::vec2 closestPoint = GetClosestPointOnBounds(closest, glm::normalize(newPos - closest));
      if (closestPoint == psc::UNUSED_VEC2)
      {
        return;
      }
      Get<CameraSys>().SetPosition(glm::mix(glm::vec2(newPos), closestPoint, followSpeed * Get<FrameLimiterSys>().GetDeltaTime<float>()));
      return;
    }

    //camera pos + direction towards target times t is point of intersection
    newPos = glm::mix(newPos, newPos + direction * min, followSpeed * Get<FrameLimiterSys>().GetDeltaTime<float>());

    //EntityManager::SetClearImmunity(debug2, true);
    Get<CameraSys>().SetPosition(glm::vec3(newPos));
  }
  /*else
  {
    Camera::SetCameraTarget(glm::vec3( glm::vec2(position), 0 ));
  }*/

}

void DynamicCamera::Activate()
{
  IsActive = true;
}

void DynamicCamera::Deactivate()
{
  IsActive = false;
}

bool DynamicCamera::InAnyBounds(glm::vec2 pos)
{
  if (bounds.empty())
  {
    return true;
  }
  for (auto it : bounds)
  {
    if (BehaviorComponentManager::GetBehavior<EntityManager::CameraBounds>(it)->InBounds(pos))
      return true;
  }
  return false;
}

glm::vec2 DynamicCamera::GetClosestPointOnBounds(glm::vec2 pos, glm::vec2 direction)
{
  float closest_distance = std::numeric_limits<float>::max();
  glm::vec2 closest_point = psc::UNUSED_VEC2;
  for (auto it : bounds)
  {
    glm::vec2 point = BehaviorComponentManager::GetBehavior<EntityManager::CameraBounds>(it)->GetClosestPoint(pos, direction);
    if (point == psc::UNUSED_VEC2)
      continue;
    float distance = glm::distance(point, pos);
    if (distance < closest_distance)
    {
      closest_distance = distance;
      closest_point = point;
    }
  }
  return closest_point;
}

void DynamicCamera::SetTrackingSpeed(float speed)
{
  followSpeed = speed;
}

void DynamicCamera::SetTrackingPos(const glm::vec4& pos)
{
  position = pos;
}

void DynamicCamera::SetInnerBounds(float width_, float height_, glm::vec2 offset)
{
  inwidth = width_;
  inheight = height_;
  inoffset = offset;
}

void DynamicCamera::AddBoundsObject(EntityID bound)
{
  bounds.push_back(bound);
}

void DynamicCamera::RemoveBoundsObject(EntityID bound)
{
  bounds.erase(std::find(bounds.begin(), bounds.end(), bound));
}

Behavior<EntityManager::Type::CameraBounds>::Behavior(EntityID id) : BaseBehavior(id)
{
  DynamicCamera::AddBoundsObject(id);
}
Behavior<EntityManager::Type::CameraBounds>::~Behavior()
{
  DynamicCamera::RemoveBoundsObject(GetID());
}

glm::vec2 Behavior<EntityManager::Type::CameraBounds>::GetClosestPoint(glm::vec2 pos, glm::vec2 direction)
{
  glm::vec4 position = TransformComponentManager::GetTranslation(GetID());
  glm::vec3 scale = TransformComponentManager::GetScale(GetID());
  glm::vec2 invDir = 1.f / direction;
  float min = ((invDir.x < 0 ? position.x + scale.x / 2 : position.x - scale.x / 2) - pos.x) * invDir.x;
  float max = ((invDir.x < 0 ? position.x - scale.x / 2 : position.x + scale.x / 2) - pos.x) * invDir.x;
  float ymin = ((invDir.y < 0 ? position.y + scale.y / 2 : position.y - scale.y / 2) - pos.y) * invDir.y;
  float ymax = ((invDir.y < 0 ? position.y - scale.y / 2 : position.y + scale.y / 2) - pos.y) * invDir.y;

  if (min > ymax || ymin > max)
    return psc::UNUSED_VEC2;

  if (ymin > min)
    min = ymin;

  return pos + direction * min;
}

bool Behavior<EntityManager::Type::CameraBounds>::InBounds(glm::vec2 pos)
{
  glm::vec4 position = TransformComponentManager::GetTranslation(GetID());
  glm::vec3 scale = TransformComponentManager::GetScale(GetID());

  if (pos.x < position.x + scale.x / 2
      && pos.x > position.x - scale.x / 2
      && pos.y < position.y + scale.y / 2
      && pos.y > position.y - scale.y / 2)
  {
    return true;
  }
  return false;
}

void Behavior<EntityManager::Type::CameraBounds>::Serialize(::std::ofstream& stream)
{
  stream << ",\n";
  stream << Tabs::TWO;
  stream << "\"behavior\" : " << "true" << "\n";
}

}

/*
static EntityID debug = GameObjectConstants::INVALID_ID;
if (debug != GameObjectConstants::INVALID_ID)
EntityManager::Destroy(debug);
debug = EntityFactory::CreateObject(EntityManager::Type::Cyclone);
TransformComponentManager::SetScale({ 100, 100, 0 }, debug);
TransformComponentManager::SetTranslation(newPos + direction * min, debug);

static EntityID debug2 = EntityFactory::CreateObject(EntityManager::Type::Cyclone);
    TransformComponentManager::SetScale({ 100, 100, 0 }, debug2);
    TransformComponentManager::SetTranslation(glm::vec4(BehaviorComponentManager::GetBehavior<EntityManager::CameraBounds>(bounds[0])->GetClosestPoint(position, direction), 15, 1), debug2);
    static EntityID debug3 = EntityFactory::CreateObject(EntityManager::Type::Cyclone);
    TransformComponentManager::SetScale({ 100, 100, 0 }, debug3);
    TransformComponentManager::SetTranslation(glm::vec4(BehaviorComponentManager::GetBehavior<EntityManager::CameraBounds>(bounds[1])->GetClosestPoint(position, direction), 15, 1), debug3);
    static EntityID debug4 = EntityFactory::CreateObject(EntityManager::Type::Cyclone);
    TransformComponentManager::SetScale({ 100, 100, 0 }, debug4);
    TransformComponentManager::SetTranslation(glm::vec4(BehaviorComponentManager::GetBehavior<EntityManager::CameraBounds>(bounds[2])->GetClosestPoint(position, direction), 15, 1), debug4);
*/