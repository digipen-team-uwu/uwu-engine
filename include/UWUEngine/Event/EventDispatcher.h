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
#include <UWUEngine/Event/EventType.h>

namespace UWUEngine
{
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
    virtual size_t ListenerCount() = 0;
    virtual size_t EventCount() = 0;

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
    size_t ListenerCount() override;
    size_t EventCount() override;

    void AddListeners(const IEventListener& listener);
    void RemoveListener(const IEventListener& listener);

  private:
    std::queue<Event<type> > events_;
    std::unordered_map<size_t, EventListener<type> > listeners_;
  };
}
#include "EventDispatcher.inl"
