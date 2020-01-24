#include <UWUEngine/Event/Type/Collision.h>
#include <utility>


CollisionEvent::CollisionEvent(CollisionInfo info):
IEvent(EventType::Collision), obj1(info.obj1), obj2(info.obj2), direction(info.direction), depth(info.depth)
{
}

CollisionEvent::CollisionEvent(EntityID obj1, EntityID obj2, glm::vec2 direction, float depth):
IEvent(EventType::Collision), obj1(obj1), obj2(obj2), direction(direction), depth(depth)
{
}

CollisionEventDispatcher::CollisionEventDispatcher():
IEventDispatcher(EventType::Collision)
{
  IEventDispatcher::DispatchEvents();
}


CollisionEventListener::CollisionEventListener(std::function<void(const CollisionEvent*)> callback):
IEventListener(EventType::Collision), callback_(std::move(callback))
{
}

void CollisionEventListener::SetFunc(std::function<void(const CollisionEvent*)> func)
{
  callback_ = func;
}

void CollisionEventListener::OnNotify(const IEvent* event) const
{
  callback_(dynamic_cast<const CollisionEvent*>(event));
}

