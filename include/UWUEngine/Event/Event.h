/******************************************************************************/
/*!
\par        Project Umbra
\file       Event.h
\author     Yi Qian
\date       2019/12/25
\brief      Event Handling

Copyright ? 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#pragma once
#include <UWUEngine/System.h>
#include <UWUEngine/Event/EventType.h>
#include <UWUEngine/Event/EventListener.h>
#include <UWUEngine/Event/EventDispatcher.h>

namespace UWUEngine
{
  class IEvent
  {
  public:
    IEvent(EventType type);
    virtual ~IEvent() = default;
    [[nodiscard]] EventType GetType() const;
    [[nodiscard]] bool IsType(EventType type) const;

  private:
    EventType type_;
  };

  template <EventType type>
  class Event final : public IEvent
  {
  public:
    ~Event() override = default;
  };

  class EventSys final : public System
  {
  public:
    EventSys(ISpace* p);
    ~EventSys() override;
    void Update() override;

    template <EventType type>
    void Push(const Event<type>& event);

    template <EventType type>
    void Register(const EventListener<type>& listener);

    template <EventType type>
    void UnRegister(const EventListener<type>& listener);

  private:
    std::map<EventType, IEventDispatcher*> dispatchers;
  };
}
#include "Event.inl"

#pragma region EventSpecialization
#include <UWUEngine/Event/Type/Collision.h>
#include <UWUEngine/Event/Type/NextScene.h>
#pragma endregion 
