#include <UWUEngine/Event/EventListener.h>

IEventListener::IEventListener(EventType type, bool autoRegister):
type_(type)
{
  if (autoRegister)
  {
    EventSystem::Register(this);
  }
}

bool IEventListener::IsType(EventType type) const
{
  return type == type_;
}

EventType IEventListener::GetType() const
{
  return type_;
}
