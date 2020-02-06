#include <UWUEngine/Event/EventDispatcher.h>

namespace UWUEngine
{
  IEventDispatcher::IEventDispatcher(EventType type) :
   type_(type)
  {
  }

  EventType IEventDispatcher::GetType() const
  {
    return type_;
  }

  bool IEventDispatcher::IsType(EventType type) const
  {
    return type == type_;
  }
}