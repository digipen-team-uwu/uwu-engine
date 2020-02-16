#pragma once
#include <UWUEngine/Systems/EventSys.h>

namespace UWUEngine
{
  template <EventType type>
  void EventSys::Push(const Event<type>& event)
  {
    const auto& pair = dispatchers.find(type);
    if (pair == dispatchers.end())
    {
      DispatcherNotFound(type);
    }
    IEventDispatcher* dispatcherBase = pair->second;
    auto* dispatcher = dynamic_cast<EventDispatcher<type>*>(dispatcherBase);

    dispatcher->Push(event);
  }

  template <EventType type>
  void EventSys::Register(const EventListener<type>& listener)
  {
    const auto& pair = dispatchers.find(type);
    if (pair == dispatchers.end())
    {
      DispatcherNotFound(type);
    }
    IEventDispatcher* dispatcherBase = pair->second;
    auto* dispatcher = dynamic_cast<EventDispatcher<type>*>(dispatcherBase);

    dispatcher->AddListeners(listener);
  }

  template <EventType type>
  void EventSys::UnRegister(const EventListener<type>& listener)
  {
    const auto& pair = dispatchers.find(type);
    if (pair == dispatchers.end())
    {
      DispatcherNotFound(type);
    }
    IEventDispatcher* dispatcherBase = pair->second;
    auto* dispatcher = dynamic_cast<EventDispatcher<type>*>(dispatcherBase);

    dispatcher->RemoveListener(listener);
  }
}
