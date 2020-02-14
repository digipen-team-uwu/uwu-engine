#pragma once
#include <map>
#include <type_traits>

namespace UWUEngine
{

class ISpace
{
public:
  ISpace(ISpace* p) : parent(p) {}
  virtual ~ISpace() = default;
  virtual void* GetObject(unsigned i) = 0;
//protected:
  ISpace* parent;
};

template <class Base, class ... Derived>
class Space : public ISpace
{
public:
  template <class T>
  T& Get();
  Space(ISpace* p = nullptr);
  ~Space();

private:
  void* GetObject(unsigned i) override;
  std::map<unsigned, Base*> objects;
  static_assert((std::is_base_of_v<Base, Derived> && ...), "All objects in a space need to be of the same base type.");

public:
  auto begin() -> decltype(objects.begin());
  auto end() -> decltype(objects.end());

};

} // namespace UWUEngine

#include <UWUEngine/Space.template.cpp>
