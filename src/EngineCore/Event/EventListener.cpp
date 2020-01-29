#include <UWUEngine/Event/EventListener.h>

IEventListener::IEventListener(EventType type, bool autoRegister):
type_(type)
{
}

bool IEventListener::IsType(EventType type) const
{
  return type == type_;
}

EventType IEventListener::GetType() const
{
  return type_;
}
