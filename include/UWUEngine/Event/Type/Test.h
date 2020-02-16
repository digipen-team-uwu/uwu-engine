#pragma once

#include <UWUEngine/Systems/EventSys.h>

namespace UWUEngine
{
  template<>
  class Event<EventType::Test> : public IEvent
  {
  public:
    Event():IEvent(EventType::Test){}
    Event(const std::string& content) : IEvent(EventType::Test), content(content){}
    ~Event() override = default;

    const std::string content{"Default"};
  };
}
