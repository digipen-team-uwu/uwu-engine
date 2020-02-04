#pragma once

template <EventType type>
EventListener<type>::EventListener(std::function<void(const Event<type>&)> func_, EntityID id) :
  IEventListener(type), func(func_), id(id)
{
  static size_t listenerIDs = 0;
  id = listenerIDs;
  ++listenerIDs;
}

template <EventType type>
void EventListener<type>::SetFunc(std::function<void(const Event<type>&)> func_)
{
  func = func_;
}

template <EventType type>
void EventListener<type>::SetID(EntityID id)
{
  this->id = id;
}

template <EventType type>
void EventListener<type>::OnNotify(const Event<type>& event) const
{
  func(event);
}

template <EventType type>
EntityID EventListener<type>::GetID() const
{
  return id;
}
