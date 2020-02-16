#pragma once
#include <UWUEngine/Systems/EventSys.h>

namespace UWUEngine
{
  template <EventType type>
  void EventSys::Push(const Event<type>& event)
  {
    auto& dispatcher = GetDispatcher<type>();

    dispatcher.Push(event);
  }

  template <EventType type>
  void EventSys::Register(const EventListener<type>& listener)
  {
    auto& dispatcher = GetDispatcher<type>();

    dispatcher.AddListeners(listener);
  }

  template <EventType type>
  void EventSys::UnRegister(const EventListener<type>& listener)
  {
    auto& dispatcher = GetDispatcher<type>();

    dispatcher.RemoveListener(listener);
  }

  template <EventType type>
  EventDispatcher<type>& EventSys::GetDispatcher()
  {
    const auto& pair = dispatchers.find(type);
    if (pair == dispatchers.end())
    {
      DispatcherNotFound(type);
    }
    IEventDispatcher* dispatcherBase = pair->second;
    return dynamic_cast<EventDispatcher<type>&>(*dispatcherBase);
  }
}
