/******************************************************************************/
/*!
\par        Project Umbra
\file       EventListener.h
\author     Yi Qian
\date       2019/12/25
\brief      Event Listener

Copyright ? 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#pragma once

#include <functional>
#include <UWUEngine/Event/EventType.h>

namespace UWUEngine
{
  //Forward Declarations
  template <EventType type>
  class Event;
  using EntityID = unsigned;

  class IEventListener
  {
  public:
    virtual ~IEventListener() = default;
    IEventListener(EventType type, bool autoRegister = false);
    bool IsType(EventType type) const;
    EventType GetType() const;

  private:
    EventType type_;
  };

  template <EventType type>
  class EventListener : public IEventListener
  {
  public:
    EventListener(std::function<void(const Event<type>&)> func_ = nullptr, EntityID id = 0);
    ~EventListener() override = default;

    void SetFunc(std::function<void(const Event<type>&)> func_);
    void SetID(EntityID id);
    void OnNotify(const Event<type>& event) const;

    EntityID GetID() const;

  private:
    std::function<void(const Event<type>&)> func;
    EntityID id{ 0 };
  };
}

#include "EventListener.inl"

#define MemberFunc(func) \
  std::bind(func, this, std::placeholders::_1)
