#pragma once
#include <map>
#include <type_traits>

namespace UWUEngine
{

class ISpace
{
public:
  virtual void* GetObject(unsigned i) = 0;
};

template <class Base, class ... Derived>
class Space : ISpace
{
public:
  template <class T>
  T& Get();
  Space();
  ~Space();
private:
  void* GetObject(unsigned i) override;
  std::map<unsigned, Base*> objects;
  static_assert((std::is_base_of_v<Base, Derived> && ...), "All objects in a space need to be of the same base type.");
};

} // namespace UWUEngine

#include <UWUEngine/Space.template.cpp>
