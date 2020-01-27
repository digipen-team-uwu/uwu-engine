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
#include "EventListener.h"
#include "EventDispatcher.h"

enum class EventType
{
  Collision,
  Spine,
  Sound
};

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

template <EventType type>
void EventSystem::Push(const Event<type>& event)
{
  IEventDispatcher* dispatcherBase = dispatchers.find(type)->second;
  EventDispatcher<type>* dispatcher = dynamic_cast<EventDispatcher<type>*>(dispatcherBase);

  dispatcher->Push(event);
}

template <EventType type>
void EventSystem::Register(const EventListener<type>& listener)
{
  IEventDispatcher* dispatcherBase = dispatchers.find(type)->second;
  EventDispatcher<type>* dispatcher = dynamic_cast<EventDispatcher<type>*>(dispatcherBase);

  dispatcher->AddListeners(listener);
}

template <EventType type>
void EventSystem::UnRegister(const EventListener<type>& listener)
{
  IEventDispatcher* dispatcherBase = dispatchers.find(type)->second;
  EventDispatcher<type>* dispatcher = dynamic_cast<EventDispatcher<type>*>(dispatcherBase);

  dispatcher->RemoveListener(listener);
}

#pragma region EventSpecialization
#include <UWUEngine/Event/Type/Collision.h>
#pragma endregion 