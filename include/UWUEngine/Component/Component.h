#pragma once

#include <UWUEngine/NonCopyable.h>
#include <UWUEngine/Space.h>

namespace UWUEngine
{

using EntityID = unsigned;

class IComponent : public NonCopyable
{
public:
  virtual void Update() = 0;
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
};

} // namespace UWUEngine