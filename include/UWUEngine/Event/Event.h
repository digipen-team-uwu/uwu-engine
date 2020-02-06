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
#include <UWUEngine/BaseSystem.h>
#include <UWUEngine/Event/EventType.h>
#include <UWUEngine/Event/EventListener.h>
#include <UWUEngine/Event/EventDispatcher.h>

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

class EventSystem final : public BaseSystem<EventSystem>
{
public:
  EventSystem();
  ~EventSystem() override;
  void Update() override;

  template <EventType type>
  static void Push(const Event<type>& event);

  template <EventType type>
  static void Register(const EventListener<type>& listener);

  template <EventType type>
  static void UnRegister(const EventListener<type>& listener);

private:
  static std::map<EventType, IEventDispatcher*> dispatchers;
};

#include "Event.inl"

#pragma region EventSpecialization
#include <UWUEngine/Event/Type/Collision.h>
#include <UWUEngine/Event/Type/NextScene.h>
#pragma endregion 
