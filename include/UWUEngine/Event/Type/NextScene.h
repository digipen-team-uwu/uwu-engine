#pragma once
#include <UWUEngine/Event/Event.h>

template<>
class Event<EventType::SetNextScene> : public IEvent
{
public:
  Event(const std::string & name):IEvent(EventType::SetNextScene), name(name){}
  ~Event() override = default;

  std::string name;
};
