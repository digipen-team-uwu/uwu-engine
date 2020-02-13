#include <UWUEngine/Event/Event.h>
#include <UWUEngine/Event/EventListener.h>
#include <UWUEngine/Event/EventDispatcher.h>

#define RegisterDispatcher(eventType) \
dispatchers.insert({EventType::eventType, new eventType ## EventDispatcher()}); \

using namespace UWUEngine;

IEvent::IEvent(EventType type):
type_(type)
{
}

EventType IEvent::GetType() const
{
  return type_;
}

bool IEvent::IsType(EventType type) const
{
  return type == type_;
}

EventSys::EventSys(ISpace* p):
System(p)
{
  //Register all dispatchers
  dispatchers.insert({EventType::Collision, new EventDispatcher<EventType::Collision>});
  dispatchers.insert({EventType::SetNextScene, new EventDispatcher<EventType::SetNextScene>});
}

EventSys::~EventSys()
{
  for (auto dispatcher : dispatchers)
  {
    delete dispatcher.second;
  }
}

void EventSys::Update()
{
  for (auto dispatcher : dispatchers)
  {
    dispatcher.second->DispatchEvents();
  }
}
