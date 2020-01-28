#include <UWUEngine/Event/Type/Collision.h>

Event<EventType::Collision>::Event():
IEvent(EventType::Collision)
{
}

Event<EventType::Collision>::Event(EntityID obj1, EntityID obj2, glm::vec2 direction, float depth):
IEvent(EventType::Collision), obj1(obj1), obj2(obj2), direction(direction), depth(depth)
{
}
