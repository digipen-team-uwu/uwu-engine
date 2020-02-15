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

template<typename Base>
class IBaseSpace : public ISpace
{
public:
  IBaseSpace(ISpace* p) : ISpace(p) {}
protected:
  std::map<unsigned, Base*> objects;
public:
  virtual auto begin() -> decltype(objects.begin());
  virtual auto end() -> decltype(objects.end());
};

template <class Base, class ... Derived>
class Space : public IBaseSpace<Base>
{
public:
  template <class T>
  T& Get();
  Space(ISpace* p = nullptr);
  ~Space();

private:
  void* GetObject(unsigned i) override;
  static_assert((std::is_base_of_v<Base, Derived> && ...), "All objects in a space need to be of the same base type.");
};

} // namespace UWUEngine

#include <UWUEngine/Space.template.cpp>
