#pragma once
#include <UWUEngine/Space.h>

#include <UWUEngine/Order.h>

namespace UWUEngine
{

template <class Base, class ... Derived>
template <class T>
T& Space<Base, Derived...>::Get()
{
  return *static_cast<T*>(GetObject(static_cast<unsigned>(GetOrder<T>(Base{}))));
}

template <class Base, class ... Derived>
Space<Base, Derived...>::Space<Base, Derived...>() : objects((std::make_pair(static_cast<unsigned>(GetOrder<Derived>((Base*){nullptr})), new Derived(this))) ...) {}

template <class Base, class ... Derived>
Space<Base, Derived...>::~Space<Base, Derived...>()
{
  (delete dynamic_cast<Derived*>(Space<Base, Derived...>::GetObject(GetOrder<Derived>((Base*){nullptr}))), ...);
}

template <class Base, class ... Derived>
void* Space<Base, Derived...>::GetObject(unsigned i)
{
  return objects[i];
}

} // namespace UWUEngine