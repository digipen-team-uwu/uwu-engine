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

private:
  std::queue<Event<type> > events_;
  std::vector<EventListener<type> > listeners_;
};

template <EventType type>
void EventDispatcher<type>::DispatchEvents()
{
  while (!events_.empty())
  {
    IEvent* event = &events_.front();
    for (auto listener : listeners_)
    {
      listener.OnNotify(*dynamic_cast<Event<type> *>(event));
    }
    delete event;
    events_.pop();
  }
}

template <EventType type>
void EventDispatcher<type>::Push(const IEvent& event)
{
  events_.push(dynamic_cast<const Event<type>&>(event));
}

template <EventType type>
void EventDispatcher<type>::AddListeners(const IEventListener& listener)
{
  listeners_.push_back(dynamic_cast<Event<type>&>(listener));
}
