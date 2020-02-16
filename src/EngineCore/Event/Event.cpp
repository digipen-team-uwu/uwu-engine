#include <UWUEngine/Systems/EventSys.h>
#include <UWUEngine/Systems/LogSys.h>
#include <UWUEngine/Event/EventListener.h>
#include <UWUEngine/Event/EventDispatcher.h>

#include <magic_enum.hpp>

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
  dispatchers.insert({EventType::Test, new EventDispatcher<EventType::Test>});
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

void EventSys::DispatcherNotFound(EventType type)
{
  Get<LogSys>().Log(LogSys::FAILURE) << "Failed to find dispatcher for {" << magic_enum::enum_name(type) << "} event" << std::endl;
  assert(0);
}
