#include <UWUEngine/Event/Event.h>
#include <UWUEngine/Event/EventListener.h>
#include <UWUEngine/Event/EventDispatcher.h>

using namespace UWUEngine;

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
