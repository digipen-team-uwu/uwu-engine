#pragma once

#include <glm/glm.hpp>
#include <UWUEngine/Event/Event.h>

//Forward Declaration
using EntityID = unsigned int;

namespace UWUEngine
{
  template <>
 class Event<EventType::Collision> : public IEvent
  {
  public:
    Event();
    Event(EntityID obj1, EntityID obj2, glm::vec2 direction, float depth);
    ~Event() override = default;

    EntityID obj1{0};
    EntityID obj2{0};
    glm::vec2 direction{0};
    float depth{0};
  };

  template <>
  void EventDispatcher<EventType::Collision>::DispatchEvents();
}