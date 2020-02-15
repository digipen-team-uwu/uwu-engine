#pragma once
#include <UWUEngine/System.h>
#include <UWUEngine/Space.h>
#include <UWUEngine/Systems/Order.h>

namespace UWUEngine
{

template <class T>
T& System::Get()
{
  return *static_cast<T*>(parent->GetObject(static_cast<unsigned>(GetOrder<T>())));
}

template <class T>
T& System::Get() const
{
  return *static_cast<T*>(parent->GetObject(static_cast<unsigned>(GetOrder<T>())));
}

} // namespace UWUEngine
