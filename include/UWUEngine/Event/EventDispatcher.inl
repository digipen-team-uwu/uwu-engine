#pragma once

namespace UWUEngine
{
  template <EventType type>
  void EventDispatcher<type>::DispatchEvents()
  {
    while (!events_.empty())
    {
      IEvent* event = &events_.front();
      Event<type>& eventOfType = *dynamic_cast<Event<type>*>(event);
      for (const auto& listener : listeners_)
      {
        listener.second.OnNotify(eventOfType);
      }
      events_.pop();
    }
  }

  template <EventType type>
  void EventDispatcher<type>::Push(const IEvent& event)
  {
    const Event<type>& eventReference = dynamic_cast<const Event<type>&>(event);
    events_.push(std::move(eventReference));
  }

  template <EventType type>
  void EventDispatcher<type>::AddListeners(const IEventListener& listener)
  {
    const EventListener<type>& listenerType = dynamic_cast<const EventListener<type>&>(listener);

    listeners_.insert({ listenerType.GetID(), listenerType });
  }

  template <EventType type>
  void EventDispatcher<type>::RemoveListener(const IEventListener& listener)
  {
    const EventListener<type>& listenerType = dynamic_cast<const EventListener<type>&>(listener);

    listeners_.erase(listenerType.GetID());
  }
}