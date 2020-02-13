#pragma once
#include "Event.h"

namespace UWUEngine
{
  template <EventType type>
  void EventSys::Push(const Event<type>& event)
  {
    IEventDispatcher* dispatcherBase = dispatchers.find(type)->second;
    EventDispatcher<type>* dispatcher = dynamic_cast<EventDispatcher<type>*>(dispatcherBase);

    dispatcher->Push(event);
  }

  template <EventType type>
  void EventSys::Register(const EventListener<type>& listener)
  {
    IEventDispatcher* dispatcherBase = dispatchers.find(type)->second;
    EventDispatcher<type>* dispatcher = dynamic_cast<EventDispatcher<type>*>(dispatcherBase);

    dispatcher->AddListeners(listener);
  }

  template <EventType type>
  void EventSys::UnRegister(const EventListener<type>& listener)
  {
    IEventDispatcher* dispatcherBase = dispatchers.find(type)->second;
    EventDispatcher<type>* dispatcher = dynamic_cast<EventDispatcher<type>*>(dispatcherBase);

    dispatcher->RemoveListener(listener);
  }
}
