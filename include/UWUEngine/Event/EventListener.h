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

//Forward Declarations
enum class EventType;
template <EventType type>
class Event;

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
  EventListener(std::function<void(Event<type>)> func_ = nullptr) :
  IEventListener(type), func(func_){}
  ~EventListener() override = default;

  void SetFunc(std::function<void(Event<type>)> func_)
  {
    func = func_;
  }
  void OnNotify(const Event<type>& event) const
  {
    func(event);
  }

private:
  std::function<void(Event<type>)> func;
};
