#include <UWUEngine/Event/Event.h>
#include <UWUEngine/Event/EventListener.h>

//Event Dispatchers
#include <UWUEngine/Event/Type/Collision.h>

#define RegisterDispatcher(eventType) \
dispatchers.insert({EventType::eventType, new eventType ## EventDispatcher()}); \

std::map<EventType, IEventDispatcher*> EventSystem::dispatchers;

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

IEventDispatcher::IEventDispatcher(EventType type):
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

void IEventDispatcher::AddListener(IEventListener* listener)
{
  listeners_.push_back(listener);
}

void IEventDispatcher::Push(IEvent* event)
{
  events_.push(event);
}

void IEventDispatcher::DispatchEvents()
{
  while (!events_.empty())
  {
    IEvent* event = events_.front();
    for (auto listener : listeners_)
    {
      listener->OnNotify(event);
    }
    delete event;
    events_.pop();
  }
}

EventSystem::EventSystem()
{
  //Register event dispatchers here
  RegisterDispatcher(Collision)
}

EventSystem::~EventSystem()
{
  for (auto dispatcher : dispatchers)
  {
    delete dispatcher.second;
  }
}

void EventSystem::Update()
{
  for (auto dispatcher : dispatchers)
  {
    dispatcher.second->DispatchEvents();
  }
}

void EventSystem::Push(IEvent* event)
{
  dispatchers.find(event->GetType())->second->Push(event);
}

void EventSystem::Register(IEventListener*listener)
{
  dispatchers.find(listener->GetType())->second->AddListener(listener);
}
