
#pragma once
#include <UWUEngine/Event/Event.h>

#include <UWUEngine/Physics/Colliders/Collider.h>
#include <glm/glm.hpp>

using EntityID = unsigned int;

template <>
class Event<EventType::Collision> : public IEvent
{
public:
  Event(CollisionInfo info);
  Event(EntityID obj1, EntityID obj2, glm::vec2 direction, float depth);
  ~Event() override = default;

  EntityID obj1;
  EntityID obj2;
  glm::vec2 direction;
  float depth;
};
