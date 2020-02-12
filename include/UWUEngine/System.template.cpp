#pragma once
#include <UWUEngine/System.h>

#include <UWUEngine/Space.h>
#include <UWUEngine/Order.h>

namespace UWUEngine
{

template <class T>
T& System::Get()
{
  return *static_cast<T*>(parent->GetObject(static_cast<unsigned>(GetOrder<T>(this))));
}

} // namespace UWUEngine