#pragma once
#include <array>
#include <UWUEngine/Order.h>

namespace UWUEngine
{

template <class Base, class ... Derived>
class Space
{
public:
  template <class T>
  T& Get()
  {
    return *dynamic_cast<T*>(GetObject(static_cast<unsigned>(GetOrder<T>())));
  }
private:
  Base* GetObject(unsigned i)
  {
    return objects[i];
  }
  std::array<Base*, sizeof...(Derived)> objects = { (new Derived) ... };
  static_assert((std::is_base_of_v<Base, Derived>&& ...), "All objects in a space need to be of the same base type.");
};

} // namespace UWUEngine
