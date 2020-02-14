#pragma once
#include <UWUEngine/Space.h> 
#include <UWUEngine/Systems/Order.h>

namespace UWUEngine
{

template <class Base, class ... Derived>
template <class T>
T& Space<Base, Derived...>::Get()
{
  return *static_cast<T*>(GetObject(static_cast<unsigned>(GetOrder<T>())));
}

template <class Base, class ... Derived>
Space<Base, Derived...>::Space<Base, Derived...>(ISpace* p) :
  ISpace(p),
  objects{}
{
  ((objects.insert(((std::make_pair(static_cast<unsigned>(GetOrder<Derived>()), static_cast<Base*>(new Derived(this))))))), ...);
}

template <class Base, class ... Derived>
Space<Base, Derived...>::~Space<Base, Derived...>()
{
  (delete (dynamic_cast<Derived*>(static_cast<Base*>(GetObject(static_cast<unsigned>(GetOrder<Derived>()))))), ...);
}

template <class Base, class ... Derived>
void* Space<Base, Derived...>::GetObject(unsigned i)
{
  return objects[i];
}

template <class Base, class ... Derived>
auto Space<Base, Derived...>::begin() -> decltype(objects.begin())
{
  return objects.begin();
}

template <class Base, class ... Derived>
auto Space<Base, Derived...>::end() -> decltype(objects.end())
{
  return objects.end();
}

} // namespace UWUEngine