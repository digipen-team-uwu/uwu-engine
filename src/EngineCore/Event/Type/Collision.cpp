#include <UWUEngine/Event/Type/Collision.h>
#include <utility>


Event<EventType::Collision>::Event<EventType::Collision>(CollisionInfo info):
IEvent(EventType::Collision), obj1(info.obj1), obj2(info.obj2), direction(info.direction), depth(info.depth)
{
}

Event<EventType::Collision>::Event<EventType::Collision>(EntityID obj1, EntityID obj2, glm::vec2 direction, float depth):
IEvent(EventType::Collision), obj1(obj1), obj2(obj2), direction(direction), depth(depth)
{
}
