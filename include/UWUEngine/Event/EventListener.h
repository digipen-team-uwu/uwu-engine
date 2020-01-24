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
#include <UWUEngine/Event/Event.h>

class IEventListener
{
public:
  virtual ~IEventListener() = default;
  IEventListener(EventType type, bool autoRegister = false);
  [[nodiscard]] bool IsType(EventType type) const;
  [[nodiscard]] EventType GetType() const;

  virtual void OnNotify(const IEvent* event) const = 0;

private:
  EventType type_;
};
