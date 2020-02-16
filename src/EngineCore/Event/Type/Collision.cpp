#include <UWUEngine/Event/Type/Collision.h>
#include <UWUEngine/Event/EventDispatcher.h>

namespace UWUEngine
{
  bool IsCollisionEventRelevant(Event<EventType::Collision> event, EntityID id)
  {
    return (event.obj1 == id) || (event.obj2 == id);
  }

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
      Event<EventType::Collision>& eventCollision = *dynamic_cast<Event<EventType::Collision>*>(event);
      for (const auto& listener : listeners_)
      {
        if (IsCollisionEventRelevant(eventCollision, listener.second.GetID()) || !listener.second.GetID())
        {
          listener.second.OnNotify(eventCollision);
        }
      }
      events_.pop();
    }
  }
}
