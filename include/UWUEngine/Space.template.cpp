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
Space<Base, Derived...>::Space(ISpace* p) :
  IBaseSpace<Base>(p)
{
  ((IBaseSpace<Base>::objects.insert(((std::make_pair(static_cast<unsigned>(GetOrder<Derived>()), static_cast<Base*>(new Derived(this))))))), ...);
}

template <class Base, class ... Derived>
Space<Base, Derived...>::~Space()
{
  (delete (dynamic_cast<Derived*>(static_cast<Base*>(GetObject(static_cast<unsigned>(GetOrder<Derived>()))))), ...);
}

template <class Base, class ... Derived>
void* Space<Base, Derived...>::GetObject(unsigned i)
{
  return IBaseSpace<Base>::objects[i];
}

template <class Base>
auto IBaseSpace<Base>::begin() -> decltype(objects.begin())
{
  return objects.begin();
}

template <class Base>
auto IBaseSpace<Base>::end() -> decltype(objects.end())
{
  return objects.end();
}

} // namespace UWUEngine