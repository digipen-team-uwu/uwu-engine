/******************************************************************************/
/*!
\par        Project Umbra
\file       EventSystem.h
\author     Yi Qian
\date       2019/12/25
\brief      Event Handling

Copyright ? 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#pragma once

#include <list>
#include <queue>
#include <GLFW/glfw3.h>

#include <UWUEngine/BaseSystem.h>
#include <UWUEngine/Event/EventListener.h>

enum class EventType
{
  COLLISION,

  COUNT
};

struct Event
{
  //Constructor
  Event():
  timeStamp(glfwGetTime())
  {}

  //Data
  EventType type{};
  double timeStamp;
  void* data{};
};

namespace std
{
  template<>
  struct less<Event>
  {
    bool operator()(const Event& lhs, const Event& rhs) const
    {
      return lhs.timeStamp < rhs.timeStamp;
    }
  };
}

class EventSystem final : public BaseSystem<EventSystem>
{
public:
  EventSystem() = default;
  ~EventSystem() override = default;
  void Update() override;

  static void Push(const Event& event);

private:
  //Functions
  void DispatchEvents();

  //Data
  static std::array<
  std::list<EventListener>,
  static_cast<size_t>(EventType::COUNT)>
  listeners;

  static std::priority_queue<Event> eventQueue;
};
