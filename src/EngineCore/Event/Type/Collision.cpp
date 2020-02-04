#include <UWUEngine/Event/Type/Collision.h>
#include <UWUEngine/Event/EventDispatcher.h>

Event<EventType::Collision>::Event():
IEvent(EventType::Collision)
{
}

Event<EventType::Collision>::Event(EntityID obj1, EntityID obj2, glm::vec2 direction, float depth):
IEvent(EventType::Collision), obj1(obj1), obj2(obj2), direction(direction), depth(depth)
{
}

template<>
void EventDispatcher<EventType::Collision>::DispatchEvents()
{
  while (!events_.empty())
  {
    IEvent* event = &events_.front();
    for (auto listener : listeners_)
    {
      
      listener.second.OnNotify(*dynamic_cast<Event<EventType::Collision>*>(event));
    }
    events_.pop();
  }
}
