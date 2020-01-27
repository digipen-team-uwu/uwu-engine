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
  EventListener(std::function<void(const Event<type> &)> func_ = nullptr) :
  IEventListener(type), func(func_)
  {
    static size_t listenerIDs = 0;
    id = listenerIDs;
    ++listenerIDs;
  }
  ~EventListener() override = default;

  void SetFunc(std::function<void(const Event<type>&)> func_)
  {
    func = func_;
  }

  void OnNotify(const Event<type>& event) const
  {
    func(event);
  }

  size_t GetID() const
  {
    return id;
  }

private:
  std::function<void(const Event<type>&)> func;
  size_t id{0};
};

#define RegisterMemberListener(type, memberFunc, name) \
  EventListener<EventType::type> name{std::bind(&memberFunc, this, std::placeholders::_1)};

#define RegisterListener(type, func, name) \
  EventListener<EventType::type> name{func};