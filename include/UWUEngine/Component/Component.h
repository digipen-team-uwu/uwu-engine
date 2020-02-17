#pragma once

#include <UWUEngine/NonCopyable.h>
#include <UWUEngine/Space.h>

namespace UWUEngine
{

using EntityID = unsigned;

template<class Comp>
class Instance
{
public:
  static_assert(std::is_base_of_v<IComponent, Comp>);
  Instance(Comp& component) : parent(&component){}

  template<class T>
  auto Get() const -> std::enable_if_t<std::is_base_of_v<IComponent, T>, T&>
  {
    return parent->Get<T>();
  }

  template <class T>
  auto Get() const -> std::enable_if_t<std::is_base_of_v<System, T>, T&>
  {
    return parent->Get<T>();
  }

private:
  Comp* parent;
};

class IComponent : public NonCopyable
{
public:
  virtual void InitObject(EntityID ID) = 0;
  virtual void ShutdownObject(EntityID ID) = 0;
  IComponent(ISpace* p) : parent(p) {}
  virtual ~IComponent() = default;
protected:
  ISpace* parent;
};

template<class Comp, class Instance>
class Component : public IComponent
{
public:
  Component(ISpace *p) : IComponent(p){}
  Instance GetInstance(EntityID ID)
  {
    return Instance(dynamic_cast<Comp*>(this), ID);
  }

  template <class T>
  auto Get() -> std::enable_if_t<std::is_base_of_v<IComponent, T>, T&>
  {
    return *static_cast<T*>(parent->GetObject(static_cast<unsigned>(GetOrder<T>())));
  }

  template <class T>
  auto Get() -> std::enable_if_t<std::is_base_of_v<System, T>, T&>
  {
    return *static_cast<T*>(parent->parent->GetObject(static_cast<unsigned>(GetOrder<T>())));
  }
};

//Caution:This function only works if you pass in a component space!!!!!
template <class T>
auto GetComponent(ISpace* componentSpace)->std::enable_if_t<std::is_base_of_v<IComponent, T>, T&>
{
  return *static_cast<T*>(componentSpace->GetObject(static_cast<unsigned>(GetOrder<T>())));
}

} // namespace UWUEngine