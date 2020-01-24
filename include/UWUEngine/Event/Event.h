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
#include <queue>
#include <vector>
#include <UWUEngine/BaseSystem.h>

//Forward declaration
class IEventListener;

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
class Event final : IEvent
{
public:
  ~Event() override;
};

class IEventDispatcher
{
public:
  IEventDispatcher(EventType type);
  virtual ~IEventDispatcher() = default;
  [[nodiscard]] EventType GetType() const;
  [[nodiscard]] bool IsType(EventType type) const;

  void AddListener(IEventListener* listener);
  void Push(IEvent* event);
  virtual void DispatchEvents();

private:
  EventType type_;
  std::queue<IEvent*> events_;
  std::vector<IEventListener*> listeners_;
};

class EventSystem final : public BaseSystem<EventSystem>
{
public:
  EventSystem();
  ~EventSystem() override;
  void Update() override;

  static void Push(IEvent* event);
  static void Register(IEventListener*listener);

private:
  static std::map<EventType, IEventDispatcher*> dispatchers;
};
