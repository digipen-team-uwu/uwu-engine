
#pragma once

#include <UWUEngine/Event/EventListener.h>
#include <UWUEngine/Physics/Colliders/Collider.h>
#include <glm/glm.hpp>

using EntityID = unsigned int;

class CollisionEvent : public IEvent
{
public:
  CollisionEvent(CollisionInfo info);
  CollisionEvent(EntityID obj1, EntityID obj2, glm::vec2 direction, float depth);
  ~CollisionEvent() override = default;

  EntityID obj1;
  EntityID obj2;
  glm::vec2 direction;
  float depth;
};

class CollisionEventDispatcher : public IEventDispatcher
{
public:
  CollisionEventDispatcher();
  ~CollisionEventDispatcher() override = default;
};

class CollisionEventListener : public IEventListener
{
public:
  CollisionEventListener(std::function<void(const CollisionEvent*)> callback = nullptr);
  ~CollisionEventListener() override = default;

  void SetFunc(std::function<void(const CollisionEvent*)> func);
  void OnNotify(const IEvent* event) const override;

private:
  std::function<void(const CollisionEvent*)> callback_;
};
