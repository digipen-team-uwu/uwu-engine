#pragma once

#include <UWUEngine/NonCopyable.h>
#include <UWUEngine/Space.h>

namespace UWUEngine
{

using EntityID = unsigned;

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
  auto& Get() -> std::enable_if_t<std::is_base_of_v<Component, T>>
  {
    return *static_cast<T*>(parent->GetObject(static_cast<unsigned>(GetOrder<T>())));
  }
};

} // namespace UWUEngine