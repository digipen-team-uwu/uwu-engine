/******************************************************************************/
/*!
\par        Project Umbra
\file       EventDispatcher.h
\author     Yi Qian
\date       2020/01/24
\brief      Event Dispatcher

Copyright ? 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#pragma once
#include <queue>
#include <unordered_map>

//Forward Declaration
class IEventListener;
class IEvent;

class IEventDispatcher
{
public:
  IEventDispatcher(EventType type);
  virtual ~IEventDispatcher() = default;
  EventType GetType() const;
  bool IsType(EventType type) const;

  virtual void DispatchEvents() = 0;
  virtual void Push(const IEvent& event) = 0;

private:
  EventType type_;
};

template<EventType type>
class EventDispatcher final : public IEventDispatcher
{
public:
  EventDispatcher():
  IEventDispatcher(type){}
  ~EventDispatcher() override{};

  void DispatchEvents() override;
  void Push(const IEvent& event) override;
  void AddListeners(const IEventListener& listener);
  void RemoveListener(const IEventListener& listener);

private:
  std::queue<Event<type> > events_;
  std::unordered_map<size_t, EventListener<type> > listeners_;
};

template <EventType type>
void EventDispatcher<type>::DispatchEvents()
{
  while (!events_.empty())
  {
    IEvent* event = &events_.front();
    for (auto listener : listeners_)
    {
      listener.second.OnNotify(*dynamic_cast<Event<type> *>(event));
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

  listeners_.insert({listenerType.GetID(), listenerType});
}

template <EventType type>
void EventDispatcher<type>::RemoveListener(const IEventListener& listener)
{
  const EventListener<type>& listenerType = dynamic_cast<const EventListener<type>&>(listener);

  listeners_.erase(listenerType.GetID());
}
